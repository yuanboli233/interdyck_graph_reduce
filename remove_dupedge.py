import sys

if len(sys.argv) != 2:
    print("Usage: python3 remove_dupedge.py <dotfile>")

dotfile = sys.argv[-1]
tmpname = "tmp_remove_dup_edge_py"

if __name__ == "__main__":
    with open(dotfile, "r") as f:
        s = set()
        for line in f:
            if "label" not in line:
                continue
            label = line.split("\"")[1]
            openflag = ("o" in label)
            fromnode = line.split("[")[0].split("->")[0]
            tonode = line.split("[")[0].split("->")[-1]
            label = label[1:]
            if openflag is False:
                tmp = fromnode
                fromnode = tonode
                tonode = tmp
            sig = fromnode + " " + tonode + " " + label
            if sig in s:
                continue
            s.add(sig)

            print(fromnode + "->" + tonode + "[label=\"o" + label + "\"]")

