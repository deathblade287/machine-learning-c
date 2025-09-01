class eq:
    def __init__(self, eq: str):
        self.eq = eq
        self.symbols = []
        for char in eq:
            if char.isalpha():
                self.symbols.append(symbol(char))

class symbol:
    def __init__(self, symb: str):
        if (type(symb) is not str or len(symb) != 1):
            raise ValueError("The symbol has to be a single charecter string. Please check type and length")

        self.symb = symb

    def __repr__(self):
        return str(self.symb)

    def __add__(self, s):
        return f"{self.symb} + {s.symb}"
    def __pow__(self, p):
        return f"{self.symb}**{p}"

x = symbol("x")
y = symbol("y")
print(x + y)
print(x**2)

equation = eq("x + y = 10")
print(equation.symbols)
