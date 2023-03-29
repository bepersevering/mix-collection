class Duck: 
    def swim(self):
        print("Duck swimming")
    def fly(self):
        print("Duck flying")
class Whale:
    def swim(self):
        print("Whale swimming")

for animal in [Duck(), Whale()]:
    animal.swim();
    animal.fly();

