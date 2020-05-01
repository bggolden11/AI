import csv
from Restuarant import Restuarant
from DecisionTree import DecisionTreeRoot
from DecisionTree import DecisionTreeNode
import math


def manualTest(attributeToTree,r):
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
                        print(child)
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

                    print(key_max)
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


def calculateAllEntropy(attributeToTree):
    for root in attributeToTree.values():
        root.calculateChildrenEntropy


def calculateT(restaurants: [Restuarant]):
    totalNumber: float = 0
    totalPos: float = 0
    for r in restaurants:
        if r.willWait:
            totalPos += 1
        totalNumber += 1
    return totalPos / totalNumber


def calculateChildren(currentRoot: DecisionTreeRoot, attributeToTree, r):
    if len(attributeToTree) == 1:
        return

    for i in range(len(currentRoot.children)):
        if currentRoot.children[i].yesToWillWaitProportion == 1 or currentRoot.children[i].yesToWillWaitProportion == 1:
            print(currentRoot.children[i].data)
            current = currentRoot.data
            if current == "pat":
                r = list(filter(lambda x: x.pat != currentRoot.children[i].data, r))
            if current == "est":
                r = list(filter(lambda x: x.est != currentRoot.children[i].data, r))
            if current == "hun":
                r = list(filter(lambda x: x.hun != currentRoot.children[i].data, r))
            if current == "type":
                r = list(filter(lambda x: x.type != currentRoot.children[i].data, r))
            if current == "fri":
                r = list(filter(lambda x: x.fri != currentRoot.children[i].data, r))
            if current == "rain":
                r = list(filter(lambda x: x.rain != currentRoot.children[i].data, r))
            if current == "res":
                r = list(filter(lambda x: x.res != currentRoot.children[i].data, r))
            if current == "bar":
                r = list(filter(lambda x: x.bar != currentRoot.children[i].data, r))

        if currentRoot.children[i].entropy != 1 and currentRoot.children[i].entropy != 0:
            key_max = max(attributeToTree.keys(),
                          key=(lambda k: attributeToTree[k].calculateChildrenGain(calculateT(r))))
            currentRoot.children[i].children = [attributeToTree[key_max]]

            attributeToTree = {"altTree": buildTreeFromRoot(r, "alt"), "bar": buildTreeFromRoot(r, "bar"),
                               "friTree": buildTreeFromRoot(r, "fri"),
                               "hunTree": buildTreeFromRoot(r, "hun"), "patTree": buildTreeFromRoot(r, "pat"),
                               "priceTree": buildTreeFromRoot(r, "price"), "rainTree": buildTreeFromRoot(r, "rain"),
                               "resTree": buildTreeFromRoot(r, "res"), "typeTree": buildTreeFromRoot(r, "type"),
                               "estTree": buildTreeFromRoot(r, "est")}
            finalRoot.prettyPrint()
            # calculateChildren(currentRoot.children[i].children[0], attributeToTree, r)
        else:
            if currentRoot.children[i].yesToWillWaitProportion > currentRoot.children[i].noToWillWaitProportion:
                currentRoot.children[i].children = [DecisionTreeNode("YES")]
            else:
                currentRoot.children[i].children = [DecisionTreeNode("NO")]


def makeTree(r):
    return {"altTree": buildTreeFromRoot(r, "alt"), "bar": buildTreeFromRoot(r, "bar"),
            "friTree": buildTreeFromRoot(r, "fri"),
            "hunTree": buildTreeFromRoot(r, "hun"), "patTree": buildTreeFromRoot(r, "pat"),
            "priceTree": buildTreeFromRoot(r, "price"), "rainTree": buildTreeFromRoot(r, "rain"),
            "resTree": buildTreeFromRoot(r, "res"), "typeTree": buildTreeFromRoot(r, "type"),
            "estTree": buildTreeFromRoot(r, "est")}




def filterRestuarant(current, r, data):
    print("test")
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


def compute(r, _attributeToTree, attributeToTree, root, count):

    if count == 1:
        # print(root.prettyPrint)
        print("test")
    key_max = max(_attributeToTree.keys(), key=(lambda k: _attributeToTree[k].calculateChildrenGain(calculateT(r))))

    root = _attributeToTree[key_max]

    for child in root.children:
        print(child)
        if child.yesToWillWait == 0 or child.noToWillWait == 0:
            if root.data == 'hun':
                print("tesdt")
            r = filterRestuarant(root.data, r, child.data)
            print(r)
            if child.yesToWillWait > child.noToWillWait:
                child.children = [DecisionTreeNode("YES")]
            else:
                child.children = [DecisionTreeNode("NO")]
    # if len(root.children) != len(attributeToTree[root.data]):
    #     for child in attributeToTree[root.data].children:
    #         if not root.children.__contains__(child):
    #             if
    for child in root.children:
        if child.yesToWillWait != 0 and child.noToWillWait != 0:
            _attributeToTree = makeTree(r)
            key_max = max(_attributeToTree.keys(),
                          key=(lambda k: _attributeToTree[k].calculateChildrenGain(calculateT(r))))
            # child.children = [attributeToTree[key_max]]
            count+=1
            # print(child.prettyPrint())
            temp = child
            # print(child.children[0])
            child.children = [compute(r, _attributeToTree, attributeToTree, child.children, count)]
    return root


def main():
    r = parse()
    print(" ---------")
    # altTree =
    attributeToTree = {"altTree": buildTreeFromRoot(r, "alt"), "bar": buildTreeFromRoot(r, "bar"),
                       "friTree": buildTreeFromRoot(r, "fri"),
                       "hunTree": buildTreeFromRoot(r, "hun"), "patTree": buildTreeFromRoot(r, "pat"),
                       "priceTree": buildTreeFromRoot(r, "price"), "rainTree": buildTreeFromRoot(r, "rain"),
                       "resTree": buildTreeFromRoot(r, "res"), "typeTree": buildTreeFromRoot(r, "type"),
                       "estTree": buildTreeFromRoot(r, "est")}

    print("##INIAL##")
    for a in attributeToTree.values():
        for c in a.children:
            print(c)
    print("##INIAL##")

    key_max = max(attributeToTree.keys(), key=(lambda k: attributeToTree[k].calculateChildrenGain(calculateT(r))))

    for root in attributeToTree.values():
        print(root.data + " " + str(root.calculateChildrenGain(calculateT(r))))

    print(key_max)
    # print("-------------------")
    # r = list(filter(lambda x: x.pat != "None" and x.pat != "Some", r))
    #
    # print("SIZE " + str(len(r)))
    #
    # print("##SECOND##")
    # attributeToTree = {"altTree": buildTreeFromRoot(r, "alt"), "bar": buildTreeFromRoot(r, "bar"),
    #                    "friTree": buildTreeFromRoot(r, "fri"),
    #                    "hunTree": buildTreeFromRoot(r, "hun"), "patTree": buildTreeFromRoot(r, "pat"),
    #                    "priceTree": buildTreeFromRoot(r, "price"), "rainTree": buildTreeFromRoot(r, "rain"),
    #                    "resTree": buildTreeFromRoot(r, "res"), "typeTree": buildTreeFromRoot(r, "type"),
    #                    "estTree": buildTreeFromRoot(r, "est")}
    #
    # print("##SECOND##")
    # for a in attributeToTree.values():
    #     for c in a.children:
    #         print(c)
    # print("##SECOND##")
    global finalRoot
    finalRoot = None
    # finalRoot = manualTest(attributeToTree,r)
    # = None

    # for root in attributeToTree.values():
    #     print(root.data + " " + str(root.calculateChildrenGain(calculateT(r))))
    finalRoot = compute(r, attributeToTree, attributeToTree, finalRoot, 0)


    print(finalRoot.prettyPrint())

    # r = list(filter(lambda x: x.pat != "None" and x.pat != "Some", r))
    print("-------------")

    # calculateChildren(finalRoot, attributeToTree, r)
    #
    # print(finalRoot.prettyPrint())
    # print("HELLO")
    # for root in attributeToTree.values():
    #     print(root.data + " " + str(root.calculateChildrenGain(calculateT(r))))


if __name__ == "__main__":
    main()
