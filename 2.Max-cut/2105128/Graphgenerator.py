import csv
import matplotlib.pyplot as plt

# Read CSV manually
graph_names = []
randomized_values = []
greedy_values = []
semi_greedy_values = []
local_search_values = []
grasp_values = []

with open('2105128.csv', newline='') as csvfile:
    reader = csv.reader(csvfile)
    next(reader)  # Skip first header
    next(reader)  # Skip second header
    for row in reader:
        graph_names.append(row[0])
        randomized_values.append(int(row[3]))
        greedy_values.append(int(row[4]))
        semi_greedy_values.append(int(row[5]))
        local_search_values.append(int(row[7]))
        grasp_values.append(int(row[9]))

# Number of graphs per plot
chunk_size = 10
total_graphs = len(graph_names)
num_chunks = (total_graphs + chunk_size - 1) // chunk_size  # ceil division

# Create and save separate plots
for chunk_index in range(num_chunks):
    start = chunk_index * chunk_size
    end = min(start + chunk_size, total_graphs)

    names = graph_names[start:end]
    rand_vals = randomized_values[start:end]
    greedy_vals = greedy_values[start:end]
    semi_vals = semi_greedy_values[start:end]
    local_vals = local_search_values[start:end]
    grasp_vals = grasp_values[start:end]

    x = range(len(names))
    width = 0.15

    plt.figure(figsize=(12, 6))

    plt.bar([i - 2*width for i in x], rand_vals, width=width, label='Randomized (avg)')
    plt.bar([i - width for i in x], greedy_vals, width=width, label='Greedy')
    plt.bar([i for i in x], semi_vals, width=width, label='Semi-Greedy (α=0.5)')
    plt.bar([i + width for i in x], local_vals, width=width, label='Local-Search')
    plt.bar([i + 2*width for i in x], grasp_vals, width=width, label='GRASP')

    plt.xticks(x, names, rotation=90)
    plt.xlabel('Graph')
    plt.ylabel('Cut Weight')
    plt.title(f'MAX-CUT Algorithm Performance (Graphs {start + 1}–{end})')
    plt.legend()
    plt.tight_layout()

    plt.savefig(f'plot_{chunk_index + 1}.png')
    plt.close()
