import subprocess
import sys
if len(sys.argv) != 2:
    print("Usage: python3 graphgen_forfilter.py <dotfile>")

bigen_py = "bidirected_edge_gen.py" 
removedup_py = "remove_dupedge.py" 
dotfile = sys.argv[-1]

tmp = "tmp.dot"
if __name__ == "__main__":
    cmd_bigen = ["python3", bigen_py, dotfile]
    cmd_removedup = ["python3", removedup_py, tmp]
    with open(tmp, "w") as outf:
        subprocess.call(cmd_bigen, stdout=outf)
    with open(dotfile, "w") as outf:
        subprocess.call(cmd_removedup, stdout=outf)

