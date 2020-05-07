import math


class DecisionTreeRoot(object):
    def __init__(self, data):
        self.data = data
        self.children = []
        self.entropy = 0

    def __str__(self) -> str:
        return str(self.data) + " = " + str(self.entropy)

    def prettyPrintTree(self, node, _prefix="", _last=True):
        if node.data is None:
            return

        if isinstance(node.data, bool):
            if node.data:
                print(_prefix, "`- " if _last else "|- ", "Yes", sep="")
            elif not node.data:
                print(_prefix, "`- " if _last else "|- ", "No", sep="")
        else:
            print(_prefix, "`- " if _last else "|- ", node.data, sep="")
        _prefix += "   " if _last else "|  "
        child_count = len(node.children)
        for i, child in enumerate(node.children):
            _last = i == (child_count - 1)
            if child.data is not None:
                self.prettyPrintTree(child, _prefix, _last)

    # * calcualte B where:
    # B(q) = −(q log2 q + (1 − q)log2(1 − q))
    def calcB(self, q):
        if q <= 0 or q >= 1:
            return 0
        return -(q * math.log(q, 2) + (1 - q) * math.log(1 - q, 2))

    # -----------------------------------------------

    # * Calcualte children entopy
    def calculateChildrenEntropy(self, givenEntropy):
        numChildren = len(self.children)
        totalEntropy = 0

        for child in self.children:
            totalEntropy += ((child.total / numChildren) * child.entropy)
        self.entropy = (givenEntropy - totalEntropy)
        return totalEntropy

    # -----------------------------------------------

    # Calculates total Entropu
    def calcualteTotalEntropy(self):
        total = 0
        entropy = 0
        for child in self.children:
            total += child.total
        for child in self.children:
            entropy -= (child.total / total) * math.log((child.total / total), 2)
        return 1 - self.calculateChildrenEntropy(1)

    # -----------------------------------------------

    # * Calculates total information gain
    def calculateChildrenGain(self, t: float):
        numChildren = len(self.children)
        totalGain = 0
        total = 0
        for child in self.children:
            total += child.total
        for child in self.children:
            totalGain += (child.total / total) * self.calcB(child.yesToWillWaitProportion)
        totalGain = self.calcB(t) - totalGain
        return totalGain


# ------------------------------------------------

# Used as child node
# Could have proably just used one node class
class DecisionTreeNode(object):
    def __init__(self, data):
        self.left = None
        self.right = None
        self.data = data
        self.yesToWillWait = 0
        self.noToWillWait = 0
        self.yesToWillWaitProportion = 0
        self.noToWillWaitProportion = 0
        self.total = 0
        self.entropy = None
        self.value = None
        self.children = []

    def addOneToYesWillWait(self):
        self.yesToWillWait += 1
        self.total += 1
        self.findProp()
        self.calculateEntropy()

    def calculateEntropy(self):
        if self.noToWillWaitProportion == 0 or self.yesToWillWaitProportion == 0:
            self.entropy = 0
        else:
            self.entropy = -(self.yesToWillWaitProportion * math.log(self.yesToWillWaitProportion, 2) +
                             self.noToWillWaitProportion * math.log(self.noToWillWaitProportion, 2))

    def addOneToNoWillWait(self):
        self.noToWillWait += 1
        self.total += 1
        self.findProp()
        self.calculateEntropy()

    def findProp(self):
        if self.yesToWillWait + self.noToWillWait == 0:
            self.yesToWillWaitProportion = 0
            self.noToWillWaitProportion = 0
        else:
            self.yesToWillWaitProportion = self.yesToWillWait / self.total
            self.noToWillWaitProportion = self.noToWillWait / self.total

    def __str__(self) -> str:
        return str(self.data) + " yesToWillWait = " + str(self.yesToWillWait) + " noToWillWait = " + str(
            self.noToWillWait) + " proporition = " + str(self.yesToWillWaitProportion) + " OTher proporition " + str(
            self.noToWillWaitProportion) + " Entropy = " + str(self.entropy)
