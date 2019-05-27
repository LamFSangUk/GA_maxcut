import matplotlib.pyplot as plt
import numpy as np

def draw_result():
    with open('D:\GA\prj2\hybrid_GA_under_0.10_farthest_selection\chimera_946\output\\result_28.out','r') as f:
        line = f.readline()
        arr_generation = []
        arr_avg_quality = []
        arr_avg_hamming_dist = []
        arr_best_quality = []
        arr_conv_ratio = []

        while line:
            if line.startswith('Generation'):
                _, num = line.split('#')
                num = np.int(num)
                arr_generation.append(num)

                cnt = 7
                while cnt:
                    sub_line = f.readline()
                    if sub_line.startswith('Avg  Quality'):
                        _, num = sub_line.split(':')
                        num = np.float(num)
                        arr_avg_quality.append(num)
                    elif sub_line.startswith('Avg Hamming Dist'):
                        _, num = sub_line.split(':')
                        num = np.float(num)
                        arr_avg_hamming_dist.append(num)
                    elif sub_line.startswith('Best Quality'):
                        _, num = sub_line.split(':')
                        num = np.float(num)
                        arr_best_quality.append(num)
                    elif sub_line.startswith('Convergence'):
                        _, num = sub_line.split(':')
                        num = np.float(num)
                        arr_conv_ratio.append(num)

                    cnt-=1
            line = f.readline()

        arr_avg_quality = np.array(arr_avg_quality)
        arr_avg_hamming_dist = np.array(arr_avg_hamming_dist)
        arr_best_quality = np.array(arr_best_quality)
        arr_conv_ratio = np.array(arr_conv_ratio)

        fig, host = plt.subplots()

        par1 = host.twinx()
        #par2 = host.twinx()

        #par2.spines["right"].set_position(("axes",1.2))

        #par2.spines["right"].set_visible(True)

        p1, = host.plot(arr_generation, arr_best_quality, "b-", label = "Best Quality")
        p2, = host.plot(arr_generation, arr_avg_quality, "r-", label = "Avg. Quality")
        p3, = par1.plot(arr_generation, arr_avg_hamming_dist, "y-", label = "Avg. Hamming Dist")
        #p4, = par2.plot(arr_generation, arr_conv_ratio, "g-", label = "Convergence")

        host.set_xlabel("Generation #")
        host.set_ylabel("Quality")
        par1.set_ylabel("Avg. Hamming Dist")
        #par2.set_ylabel("Convergence")

        #par2.set_ylim(0,1)

        par1.yaxis.label.set_color(p3.get_color())
        #par2.yaxis.label.set_color(p4.get_color())

        lines = [p1,p2]

        host.legend(lines, [l.get_label() for l in lines])

        plt.show()

if __name__=='__main__':
    draw_result()