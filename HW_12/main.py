import csv
from Restuarant import Restuarant
from DecisionTree import DecisionTreeRoot
from DecisionTree import DecisionTreeNode
import math


def manualTest(attributeToTree, r):
    key_max = max(attributeToTree.keys(), key=(lambda k: attributeToTree[k].calculateChildrenGain(calculateT(r))))
    finalRoot = attributeToTree[key_max]
    for child in finalRoot.children:
        print(child)
        if child.yesToWillWait == 0 or child.noToWillWait == 0:
            if child.yesToWillWait > child.noToWillWait:
                child.children = [DecisionTreeNode("YES")]
            else:
                child.children = [DecisionTreeNode("NO")]
    print(finalRoot.prettyPrint())
    r = filterRestuarant("pat", r, "None")
    r = filterRestuarant("pat", r, "Some")
    # r = filterRestuarant(root.data, r, child.data)

    # r = list(filter(lambda x: x.pat != "None" and x.pat != "Some", r))
    attributeToTree = makeTree(r)
    key_max = max(attributeToTree.keys(), key=(lambda k: attributeToTree[k].calculateChildrenGain(calculateT(r))))
    print(key_max)
    for child in finalRoot.children:
        print(child)
        if child.yesToWillWait == 0 or child.noToWillWait == 0:
            if child.yesToWillWait > child.noToWillWait:
                child.children = [DecisionTreeNode("YES")]
            else:
                child.children = [DecisionTreeNode("NO")]
        else:
            child.children = [attributeToTree[key_max]]
            for child in child.children[0].children:
                print(child)
                if child.yesToWillWait == 0 or child.noToWillWait == 0:
                    if child.yesToWillWait > child.noToWillWait:
                        child.children = [DecisionTreeNode("YES")]
                    else:
                        child.children = [DecisionTreeNode("NO")]
                else:
                    # r = list(filter(lambda x: x.hun != False, r))
                    r = filterRestuarant("hun", r, False)
                    attributeToTree = makeTree(r)
                    key_max = max(attributeToTree.keys(),
                                  key=(lambda k: attributeToTree[k].calculateChildrenGain(calculateT(r))))
                    child.children = [attributeToTree[key_max]]
                    for child in child.children[0].children:
                        if child.yesToWillWait == 0 or child.noToWillWait == 0:
                            if child.yesToWillWait > child.noToWillWait:
                                child.children = [DecisionTreeNode("YES")]
                            else:
                                child.children = [DecisionTreeNode("NO")]
                        else:
                            r = filterRestuarant("type", r, "Italian")
                            r = filterRestuarant("type", r, "Burger")
                            attributeToTree = makeTree(r)
                            key_max = max(attributeToTree.keys(),
                                          key=(lambda k: attributeToTree[k].calculateChildrenGain(calculateT(r))))
                            child.children = [attributeToTree[key_max]]
    return finalRoot


def toBoolean(s: str):
    s.strip()
    if s.strip() == "Yes":
        return True
    else:
        return False


def calculateEntropy(numYes, numNo):
    total = numYes + numNo
    propYes = numYes / total
    propNo = numNo / total
    return -(propYes * math.log(propYes, 2) +
             propNo * math.log(propNo, 2))


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
        global parentEntropy
        parentEntropy = calculateEntropy(countYesWillWait, countNoWillWait)
        return restaurants


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
    global parentEntropy
    root.calculateChildrenEntropy(parentEntropy)
    return root


def calculateT(restaurants: [Restuarant]):
    totalNumber: float = 0
    totalPos: float = 0
    for r in restaurants:
        if r.willWait:
            totalPos += 1
        totalNumber += 1
    return totalPos / totalNumber


def makeTree(r):
    return {"altTree": buildTreeFromRoot(r, "alt"), "bar": buildTreeFromRoot(r, "bar"),
            "friTree": buildTreeFromRoot(r, "fri"),
            "hunTree": buildTreeFromRoot(r, "hun"), "patTree": buildTreeFromRoot(r, "pat"),
            "priceTree": buildTreeFromRoot(r, "price"), "rainTree": buildTreeFromRoot(r, "rain"),
            "resTree": buildTreeFromRoot(r, "res"), "typeTree": buildTreeFromRoot(r, "type"),
            "estTree": buildTreeFromRoot(r, "est")}


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
    return r


def computeTree(r, _attributeToTree, attributeToTree, root, count):
    key_max = max(_attributeToTree.keys(), key=(lambda k: _attributeToTree[k].calculateChildrenGain(calculateT(r))))

    root = _attributeToTree[key_max]

    for child in root.children:
        if child.yesToWillWait == 0 or child.noToWillWait == 0:
            r = filterRestuarant(root.data, r, child.data)
            if child.yesToWillWait > child.noToWillWait:
                child.children = [DecisionTreeNode("YES")]
            else:
                child.children = [DecisionTreeNode("NO")]
    if len(root.children) != len(attributeToTree[str(root.data) + "Tree"].children):
        for child in attributeToTree[str(root.data) + "Tree"].children:
            if not any(child.data == u.data for u in root.children):
                Node = DecisionTreeNode(child.data)
                Node.children = [DecisionTreeNode("YES")]
                root.children.append(Node)
    for child in root.children:
        if child.yesToWillWait != 0 and child.noToWillWait != 0:
            _attributeToTree = makeTree(r)
            key_max = max(_attributeToTree.keys(),
                          key=(lambda k: _attributeToTree[k].calculateChildrenGain(calculateT(r))))
            count += 1

            child.children = [computeTree(r, _attributeToTree, attributeToTree, child.children, count)]
    return root


def main():
    r = parse()
    attributeToTree = makeTree(r)
    global finalRoot
    finalRoot = None
    
    print("Compute and print tree")
    print("##----------------------------------------##")

    finalRoot = computeTree(r, attributeToTree, attributeToTree, finalRoot, 0)

    print(finalRoot.prettyPrint())

    print("##----------------------------------------##")


if __name__ == "__main__":
    main()
