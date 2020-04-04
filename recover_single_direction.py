import sys

if len(sys.argv) != 3:
    print("Usage: python3 recover_single_direction.py <orig dotfile> <reduced bidirected dotfile> ")

origfile = sys.argv[1]
reducedfile = sys.argv[2]

def get_reverse_node_map():
    rmap = dict()
    with open(nodemap, "r") as f:
        for line in f:
            leftnum = line.split(":")[0].strip()
            leftnum = int(leftnum)

            rightnums = line.split(": ")[-1].strip().split()
            rightnums = [int(i.strip()) for i in rightnums]
            for rnum in rightnums:
                rmap[rnum] = leftnum
    return rmap

def get_open_edges(graphfile):
    edges = set()
    with open(graphfile, "r") as f:
        for line in f:
            if "c" in line:
                print("Error, reduced graph has --c label")
                exit(1)
            nfrom = line.split("->")[0].strip()
            nto = line.split("[")[0].split("->")[-1].strip()
            eid = line.split("--")[-1].strip().split("\"")[0].strip()
            sig = "_".join([nfrom, nto, eid])
            edges.add(sig)
    return edges
    
if __name__ == "__main__":
    reduced_edges = get_open_edges(reducedfile)
    with open(origfile, "r") as origf:
        for line in origf:
            if "label=" not in line:
                continue
            nfrom = line.split("->")[0].strip()
            nto = line.split("[")[0].split("->")[-1].strip()
            nfrom = int(nfrom)
            nto = int(nto)
            if("c" in line):
                tmp = nto
                nto = nfrom
                nfrom = tmp
            eid = line.split("--")[-1].strip().split("\"")[0].strip()
            
            if "_".join([str(nfrom), str(nto), eid])  in reduced_edges:
                print(line.strip())


