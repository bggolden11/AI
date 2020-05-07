class Restuarant:

    def __init__(self,number, alt, bar, fri, hun, pat, price, rain, res, type, est, willWait):
        self.number = number
        self.alt = alt
        self.bar = bar
        self.fri = fri
        self.hun = hun
        self.pat = pat
        self.price = price
        self.rain = rain
        self.res = res
        self.type = type
        self.est = est
        self.willWait = willWait
        self.mapToAttributeValue = {"alt": self.alt, "bar": self.bar, "fri": self.fri,
                                    "hun": self.hun, "pat": self.pat, "price": self.price,
                                    "rain": self.rain, "res": self.res, "type": self.type,
                                    "est": self.est
                                    }
        self.list = [self.alt, self.bar, self.fri, self.hun, self.pat, self.price, self.rain, self.res, self.type,
                     self.est, self.willWait]

    def __str__(self) -> str:
        return "alt = " + str(self.alt) + " bar = " + str(self.bar) + " willWait = " + str(self.willWait)
