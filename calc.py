class expression:
    def __init__(self, term1, term2, operator):
        self.term1 = term1
        self.term2 = term2
        self.operator = operator

    def __repr__(self):
        return f"{self.term1} {self.operator} {self.term2}"
    
    def __add__(self, e2):
        return expression(self, e2, '+')
    
    def __sub__(self, e2):
        return expression(self, e2, '-')


class variable:
    def __init__(self, symbol: str, power: int = 1):
        if (type(symbol) is not str or len(symbol) != 1):
            raise ValueError("The symbol has to be a single charecter string. Please check type and length")

        self.symbol = symbol
        self.power = power

    def __repr__(self):
        return f"{str(self.symbol)}**{self.power}"

    def __mul__(self, s):
        return expression(self, s, "*")

    def __pow__(self, p: int):
        return variable(self.symbol, p)
    
    def __add__(self, v2):
        return expression(self, v2, '+')
    
    def __sub__(self, v2):
        return expression(self, v2, '-')

x = variable("x")
y = variable("y")

y = x**2 + x
z = y + 5
print(z.term1)
print(z.term2)
print(z.operator)
