"""Negative controls for tools/xcompare.py (needs the owner's XBE and VS 2022).
Each case plants one deliberate bug in a copy of real recovered source; the
checker must report FAIL. Cases marked known_limit document blind spots and
must report PASS (so a silent improvement or regression is noticed).
Run: py -3 tests/negative_controls.py      log: logs/negative_controls.log
"""
import os, subprocess, sys
ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import xcompare

CASES = [
    # label, file, func, va, old, new, expect
    ("wrong-constant", "grade.c", "Grade_AddExclamations", 0x414A0, "> 999)", "> 998)", "FAIL"),
    ("reversed-condition", "grade.c", "Grade_AddBestCombo", 0x41480, "bestCombo < combo", "bestCombo > combo", "FAIL"),
    ("wrong-call-target", "stats.c", "Souls_Spend", 0xD1F40, "sub_00024D30(2, amount)", "sub_00025FD0(2, amount)", "FAIL"),
    ("wrong-global", "stats.c", "Souls_AddLifetime", 0xCF910, "g_stats.soulsLifetime += amount", "g_stats.soulsWallet += amount", "FAIL"),
    ("wrong-float-constant", "clock.c", "Clock_SetChapterTime", 0x19C0B0, "seconds *= 300.0f", "seconds *= 301.0f", "FAIL"),
    ("wrong-field", "stats.c", "Stats_Get", 0xCF790, "case 12: return s->soulsWallet", "case 12: return s->soulsLifetime", "FAIL"),
    ("wrong-calling-convention", "system.c", "Frame_Present", 0x1A7BA0, "    sub_001A7940();", "    sub_001A7940(); sub_00025FD0(1, 2);", "FAIL"),
    ("missing-function", "system.c", "Job_IsRunning", 0x57E90, "JobFunc Job_IsRunning(void)\n{\n    return g_job.func;\n}", "", "FAIL"),
    ("wrong-array-field", "grade.c", "Grade_CommitChapter", 0x40C10, "rec->grade = 4", "rec->rank[3] = 4", "FAIL"),
    ("wrong-tail-call-target", "player_obj.c", "PlayerObj_ForwardFD8", 0xCF450, "sub_000F5D40(p->unkFD8 + 0x60, src);", "sub_00171CD0((PlayerStats *)(p->unkFD8 + 0x60));", "FAIL"),
    ("wrong-struct-offset", "player_obj.c", "PlayerObj_ClearFlags22", 0xCF4E0, "p->flags[0] &= ~0x22u;", "p->flags[1] &= ~0x22u;", "FAIL"),
    ("deleted-hang", "grade.c", "Grade_CommitChapter", 0x40C10, "        for (;;)\n            ;   /* deliberate hang", "        (void)0;   /* deliberate hang", "FAIL"),
    # documented blind spots
    ("LIMIT pure negation (< vs >=)", "grade.c", "Grade_AddBestCombo", 0x41480, "bestCombo < combo", "bestCombo >= combo", "PASS"),
    ("LIMIT swapped fields both used", "stats.c", "Stats_Get", 0xCF790, "case 0:  return s->maxHealth;\n    case 1:  return s->health;", "case 0:  return s->health;\n    case 1:  return s->maxHealth;", "PASS"),
]


def main():
    out, bad = [], 0
    for label, f, func, va, old, new, expect in CASES:
        src = open(os.path.join(ROOT, "src", "game", f)).read()
        if old not in src:
            out.append(f"ERROR  {label}: pattern not found in {f}"); bad += 1; continue
        d = os.path.join(ROOT, "build", "neg", label.replace(" ", "_").replace("(", "").replace(")", "").replace("<", "lt").replace(">=", "ge"))
        os.makedirs(d, exist_ok=True)
        mf = os.path.join(d, f)
        open(mf, "w").write(src.replace(old, new, 1))
        obj = os.path.join(d, f.replace(".c", ".obj"))
        if os.path.exists(obj):
            os.remove(obj)
        subprocess.run(["cmd", "/c", os.path.join("tools", "clto.bat"), d, mf], cwd=ROOT,
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        try:
            ok = xcompare.compare(obj, func, va)
            got = "PASS" if ok else "FAIL"
        except SystemExit as e:
            got = "FAIL"   # symbol missing / object missing
        good = got == expect
        bad += not good
        out.append(f"{'ok ' if good else 'BAD'}  {label:34} expected {expect}, got {got}")
    print("\n".join(out))
    print(f"{len(CASES) - bad}/{len(CASES)} controls behaved as expected")
    open(os.path.join(ROOT, "logs", "negative_controls.log"), "w").write("\n".join(out) + "\n")
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()
