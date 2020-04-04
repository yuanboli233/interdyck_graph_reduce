import sys

if len(sys.argv) != 2:
    print("Usage: python3 bidirected_edge_gen.py <dotfile>")
    exit(0)


dotfile = sys.argv[-1]

if __name__ == "__main__":
    with open(dotfile, "r") as f:
        for line in f:
            if "[" not in line:
                continue
            nodes_str = line.split("[")[0]
            from_node = nodes_str.split("->")[0]
            to_node = nodes_str.split("->")[1]
            print(line.strip())
            
            if "o" in line:
                new_line = to_node + "->" + from_node + "[" + line.split("[")[-1].replace("o", "c")
            if "c" in line:
                new_line = to_node + "->" + from_node + "[" + line.split("[")[-1].replace("c", "o")
            print(new_line.strip())

