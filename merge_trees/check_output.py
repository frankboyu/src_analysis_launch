import os, sys

version   = sys.argv[1]
batch     = sys.argv[2]

path_volatile = "/volatile/halld/analysis/RunPeriod-2021-11/ver"+version+"/batch"+batch

for tree_name in os.listdir(path_volatile):
    if tree_name.startswith("tree"):
        print(tree_name)
        path_tree = os.path.join(path_volatile, tree_name)
        for run_name in os.listdir(path_tree):
            path_mss = "/mss/halld/RunPeriod-2021-11/analysis/ver"+version+"/"+tree_name+"/merged/"+tree_name+"_"+run_name+".root"
            if not os.path.isfile(path_mss):
                print(path_mss+" is missing")

# path_mss = "/mss/halld/RunPeriod-2021-11/analysis/ver"+version

# for tree_name in os.listdir(path_mss):
#     path_tree = os.path.join(path_mss, tree_name)
#     print(tree_name, len(os.listdir(path_tree+"/merged")))

