"""Synthetic tests for tools/xbe_inventory.py (no game bytes needed).
Run: py -3 -m unittest discover -s tests -v
"""
import os, struct, sys, tempfile, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "tools"))
from xbe_inventory import Xbe, XbeError, XOR_ENTRY, XOR_THUNK, kernel_refs

BASE = 0x10000


def make_xbe(entry=0x11000, thunk=0x11100, kind="retail", nsect=1, raw_size=0x200,
             vsize=0x300, magic=b"XBEH", thunks=(0x80000115, 0x80000126)):
    hdr_size = 0x1000
    d = bytearray(hdr_size + raw_size)
    d[0:4] = magic
    struct.pack_into("<I", d, 0x104, BASE)
    struct.pack_into("<I", d, 0x108, hdr_size)
    struct.pack_into("<I", d, 0x10C, 0x2000)
    struct.pack_into("<I", d, 0x11C, nsect)
    struct.pack_into("<I", d, 0x120, BASE + 0x200)
    struct.pack_into("<I", d, 0x128, entry ^ XOR_ENTRY[kind])
    struct.pack_into("<I", d, 0x158, thunk ^ XOR_THUNK[kind])
    # one section: .text at 0x11000, raw at file 0x1000
    struct.pack_into("<6I", d, 0x200, 6, 0x11000, vsize, hdr_size, raw_size, BASE + 0x300)
    d[0x300:0x306] = b".text\0"
    off = hdr_size + (thunk - 0x11000)
    for i, t in enumerate(thunks):
        struct.pack_into("<I", d, off + 4 * i, t)
    # code at 0x11010: call dword ptr [thunk+4]; ret
    code = b"\xff\x15" + struct.pack("<I", thunk + 4) + b"\xc3"
    d[hdr_size + 0x10:hdr_size + 0x10 + len(code)] = code
    return bytes(d)


class T(unittest.TestCase):
    def load(self, data):
        fd, p = tempfile.mkstemp(suffix=".xbe")
        os.write(fd, data); os.close(fd)
        self.addCleanup(os.remove, p)
        return Xbe(p)

    def test_retail_decode(self):
        x = self.load(make_xbe())
        self.assertEqual((x.kind, x.entry, x.thunk), ("retail", 0x11000, 0x11100))
        self.assertEqual(x.sections[0]["name"], ".text")
        self.assertEqual(x.num_thunks(), 2)

    def test_debug_decode(self):
        x = self.load(make_xbe(kind="debug"))
        self.assertEqual(x.kind, "debug")

    def test_kernel_ref_counted(self):
        x = self.load(make_xbe())
        self.assertEqual(kernel_refs(x, 0x11010, 7), 1)
        self.assertEqual(kernel_refs(x, 0x11017, 8), 0)

    def test_zero_fill_not_readable(self):
        x = self.load(make_xbe())
        with self.assertRaises(XbeError):
            x.read_va(0x111F0, 0x20)   # crosses raw end 0x11200 into zero fill

    # negative controls: malformed input must fail, not guess
    def test_bad_magic(self):
        with self.assertRaises(XbeError):
            self.load(make_xbe(magic=b"MZ\0\0"))

    def test_entry_outside_image(self):
        with self.assertRaises(XbeError):
            self.load(make_xbe(entry=0x900000))

    def test_truncated(self):
        with self.assertRaises(XbeError):
            self.load(make_xbe()[:0x100])

    def test_section_past_eof(self):
        d = bytearray(make_xbe())
        struct.pack_into("<I", d, 0x200 + 16, 0x10000)  # raw size way past EOF
        with self.assertRaises(XbeError):
            self.load(bytes(d))

    def test_thunk_no_terminator(self):
        with self.assertRaises(XbeError):
            x = self.load(make_xbe(thunks=[0x80000001] * 64))
            x.num_thunks()   # runs off the raw data -> error


if __name__ == "__main__":
    unittest.main()
