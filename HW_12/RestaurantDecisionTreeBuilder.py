import csv
from Restuarant import Restuarant
from DecisionTree import DecisionTreeRoot
from DecisionTree import DecisionTreeNode


# ---------------------------------------------------------

def toBoolean(s: str):
    s.strip()
    if s.strip() == "Yes":
        return True
    else:
        return False


# ---------------------------------------------------------


def parse():
    with open('restuarant.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        restaurants = []
        countYesWillWait = 0
        countNoWillWait = 0
        num = 0
        for row in csv_reader:
            r = Restuarant(num, toBoolean(row[0]), toBoolean(row[1]), toBoolean(row[2]), toBoolean(row[3]),
                           row[4].strip(),
                           row[5].strip(), toBoolean(row[6]), toBoolean(row[7]), row[8].strip(), row[9].strip(),
                           toBoolean(row[10]))
            if r.willWait:
                countYesWillWait += 1
            else:
                countNoWillWait += 1
            restaurants.append(r)
            num += 1
        return restaurants


# ---------------------------------------------------------

def buildTreeFromRoot(restaurant, attribute):
    root = DecisionTreeRoot(attribute)
    for r in restaurant:
        if not any(child.data == r.mapToAttributeValue[attribute] for child in root.children):
            root.children.append(DecisionTreeNode(r.mapToAttributeValue[attribute]))
        for child in root.children:
            if child.data == r.mapToAttributeValue[attribute]:
                if r.willWait:
                    child.addOneToYesWillWait()
                else:
                    child.addOneToNoWillWait()
    return root


# ---------------------------------------------------------

def calculateT(restaurants: [Restuarant]):
    totalNumber: float = 0
    totalPos: float = 0
    for r in restaurants:
        if r.willWait:
            totalPos += 1
        totalNumber += 1
    return totalPos / totalNumber

# ---------------------------------------------------------

# * Creates Map of description to DecisionTree
def makeTree(r):
    return {"altTree": buildTreeFromRoot(r, "alt"), "bar": buildTreeFromRoot(r, "bar"),
            "friTree": buildTreeFromRoot(r, "fri"),
            "hunTree": buildTreeFromRoot(r, "hun"), "patTree": buildTreeFromRoot(r, "pat"),
            "priceTree": buildTreeFromRoot(r, "price"), "rainTree": buildTreeFromRoot(r, "rain"),
            "resTree": buildTreeFromRoot(r, "res"), "typeTree": buildTreeFromRoot(r, "type"),
            "estTree": buildTreeFromRoot(r, "est")}

# ---------------------------------------------------------

# * Function to filter Restuarants
def filterRestuarant(current, r, data):
    if current == "pat":
        r = list(filter(lambda x: x.pat != data, r))
    if current == "est":
        r = list(filter(lambda x: x.est != data, r))
    if current == "hun":
        r = list(filter(lambda x: x.hun != data, r))
    if current == "type":
        r = list(filter(lambda x: x.type != data, r))
    if current == "fri":
        r = list(filter(lambda x: x.fri != data, r))
    if current == "rain":
        r = list(filter(lambda x: x.rain != data, r))
    if current == "res":
        r = list(filter(lambda x: x.res != data, r))
    if current == "bar":
        r = list(filter(lambda x: x.bar != data, r))
    if current == "alt":
        r = list(filter(lambda x: x.alt != data, r))
    if current == "price":
        r = list(filter(lambda x: x.price != data, r))

    return r


# ---------------------------------------------------------

# * Main Driver Function for computing final decision tree
# * Recursively calls itself until final tree is built
# * Splits data recursively
def computeTree(r, currentAttributeToTree, listOfAllAttributeToTree, root, count):
    key_max = max(currentAttributeToTree.keys(), key=(lambda k: currentAttributeToTree[k].calculateChildrenGain(calculateT(r))))
    root = currentAttributeToTree[key_max]
    for child in root.children:
        if child.yesToWillWait == 0 or child.noToWillWait == 0:
            r = filterRestuarant(root.data, r, child.data)
            if child.yesToWillWait > child.noToWillWait:
                child.children = [DecisionTreeNode("YES")]
            else:
                child.children = [DecisionTreeNode("NO")]

    # * SPECIAL CASE: current iteration missing attribute
    for child in listOfAllAttributeToTree[0][str(root.data) + "Tree"].children:
        if not any(child.data == u.data for u in root.children):
            # Iterates through previous iteration until current one is found
            for a in listOfAllAttributeToTree[::-1]:
                if child in a[str(root.data) + "Tree"].children:
                    Node = DecisionTreeNode(child.data)
                    if child.yesToWillWait >= child.noToWillWait:
                        Node.children = [DecisionTreeNode("YES")]
                    else:
                        Node.children = [DecisionTreeNode("NO")]
                    root.children.append(Node)
                    break
    for child in root.children:
        if child.yesToWillWait != 0 and child.noToWillWait != 0:
            currentAttributeToTree = makeTree(r)
            key_max = max(currentAttributeToTree.keys(),
                          key=(lambda k: currentAttributeToTree[k].calculateChildrenGain(calculateT(r))))
            count += 1
            listOfAllAttributeToTree.append(currentAttributeToTree)
            child.children = [computeTree(r, currentAttributeToTree, listOfAllAttributeToTree, child.children, count)]
    return root

# * MAIN FUNCTION
def main():
    # * Parse Data
    restaurants: list[Restuarant] = parse()

    attributeToTree = makeTree(restaurants)
    global finalRoot
    finalRoot = None

    print()
    print("** COMPUTE AND PRINT TREE **")
    print("##----------------------------------------##")

    finalRoot = computeTree(restaurants, attributeToTree, [attributeToTree], finalRoot, 0)

    finalRoot.pprint_tree(finalRoot)

    print("##----------------------------------------##")


if __name__ == "__main__":
    main()
