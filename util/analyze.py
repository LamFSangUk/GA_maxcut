import numpy as np
import os
import glob

def analyze(path):
    dirs = glob.glob(path+'/*')
    print(dirs)

    for dir_name in dirs:
        if os.path.isdir(dir_name):

            files = glob.glob(dir_name+'/output/*.out')

            bests = []
            #avgs = []
            #avg_ham_dists = []
            for out in files:
                with open(out,"r") as f:
                    lines = f.readlines()[-9:]

                    for line in lines:
                        if line.startswith("Best Quality"):
                            _, num = line.split(':')
                            num = float(num)
                            bests.append(num)
                        #elif line.startswith("Avg  Quality"):
                        #    _, num = line.split(':')
                        #    num = float(num)
                        #    avgs.append(num)
                        #elif line.startswith("Avg Hamming Dist"):
                        #    _, num = line.split(':')
                        #    num = float(num)
                        #    avg_ham_dists.append(num)


            print(bests)
            filename = dir_name+'.analysis'
            with open (filename,'w') as f:
                f.write("Best Solution: \t"+ str(max(bests)) + '\n')
                f.write("Avg Solution: \t" + str(np.mean(bests)) + '\n')
                f.write("Std.dev: \t\t" + str(np.std(bests)) + '\n')

                #f.write('\n')
                #f.write("Avg Hamming Dist: \t"+str(np.mean(avg_ham_dists)))

def generation_count(path):
    dirs = glob.glob(path+'/*')
    print(dirs)

    for dir_name in dirs:
        if os.path.isdir(dir_name):

            files = glob.glob(dir_name+'/output/*.out')

            gen = []
            for out in files:
                with open(out,"r") as f:
                    lines = f.readlines()[-9:]

                    for line in lines:
                        if line.startswith("Generation"):
                            _, num = line.split('#')
                            num = float(num)
                            gen.append(num)
                            break


            print(dir_name, sum(gen)/len(gen))


if __name__ == "__main__":
    analyze('../test')
    #generation_count('../hybrid_GA_under_0.10_farthest_selection')
