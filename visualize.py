import subprocess
import graphviz

# Run the bison command
subprocess.run(['bison', '-y', '-g', '-d', 'parser.y'])

# Read the DOT file
with open('y.dot', 'r') as dotfile:
    dotgraph = dotfile.read()

# Create a Graphviz object
graph = graphviz.Source(dotgraph)

# Save the visualization to a file in PNG format
graph.render('Parser Automata', format='png', view=True)
