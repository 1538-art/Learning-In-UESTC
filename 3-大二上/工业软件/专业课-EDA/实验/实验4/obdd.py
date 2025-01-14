import os
class BDDNode:
    def __init__(self, variable=None, high=None, low=None):
        self.variable = variable
        self.high = high
        self.low = low
        self.id = -1
    def __hash__(self):
        return hash((self.variable, id(self.high), id(self.low)))
    def __eq__(self, other):
        return (self.variable, id(self.high), id(self.low)) == (other.variable, id(other.high), id(other.low))

def parse(expression):
    variables = []
    words = expression.split(" ")
    for word in words:
        if word!="and" and word!="or" and word!="not" and word not in variables:
            variables.append(word)
    return variables

def evaluate(expression,values):
    expression = expression.replace("and", "&").replace("or","|").replace("not","!")
    for i in range(len(init_variables)):
        expression=expression.replace(init_variables[i], str(values[i]))
    expression = expression.replace('&', "and").replace("|","or").replace("!","not")
    result = int(eval(expression))
    return result

def build_bdd(expression,variables, values):
    if len(variables) == 0:
        result = evaluate(expression,values)
        return BDDNode(variable='terminal', high=result, low=None)
    current_var = variables[0]
    high_subtree = build_bdd(expression,variables[1:], values + [True])
    low_subtree = build_bdd(expression,variables[1:], values + [False])
    return BDDNode(variable=current_var, high=high_subtree, low=low_subtree)

def merge_identical_subtrees(node, visit):
    print("合并同构结点")

def remove_redundant_nodes(node):
    print("移除冗余结点")

def generate_dot(node, dot_dict, node_ids):
    global nodenum
    if node.id !=-1:
        return node.id
    else:
        node.id=nodenum
        nodenum=nodenum+1
    label = node.variable if node.variable != 'terminal' else str(node.high)
    dot_dict['nodes'].append(f"node{node.id} [label=\"{label}\"]")
    if node.variable != 'terminal':
        high_id = generate_dot(node.high, dot_dict, node_ids)
        low_id = generate_dot(node.low, dot_dict, node_ids)
        dot_dict['edges'].append(f"node{node.id} -> node{high_id} [label=\"1\"]")
        dot_dict['edges'].append(f"node{node.id} -> node{low_id} [label=\"0\"]")
    return node.id

def print_dot(node):
    dot_dict = {'nodes': [], 'edges': []}
    node_ids = {}
    generate_dot(node, dot_dict, node_ids)
    dot_output = "digraph BDD {\n"
    dot_output += "\n".join(dot_dict['nodes']) + "\n"
    dot_output += "\n".join(dot_dict['edges']) + "\n"
    dot_output += "}"
    print(dot_output)

f= open(os.path.join(os.path.dirname(__file__), "input.txt"),'r',encoding='utf-8')
expression = f.readline()
init_variables = parse(expression)
init_variables.sort()
bdd_root = build_bdd(expression,init_variables, [])
bbd_root = merge_identical_subtrees(bdd_root, {})
bbd_root = remove_redundant_nodes(bbd_root)
nodenum=0
print_dot(bdd_root)
