import random

class Entity:
    def __init__(self, name, x, y, energy):
        self.name = name
        self.x = x
        self.y = y
        self.energy = energy
        self.alive = True

    def move(self, max_x, max_y):
        self.x = (self.x + random.randint(-1, 1)) % max_x
        self.y = (self.y + random.randint(-1, 1)) % max_y

    def is_alive(self):
        return self.alive and self.energy > 0

    def __str__(self):
        return f"{self.name} - Pos: ({self.x}, {self.y}), Energy: {self.energy}"


class Plant(Entity):
    def __init__(self, name, x, y, energy, growth_rate):
        super().__init__(name, x, y, energy)
        self.growth_rate = growth_rate

    def act(self):
        if self.is_alive():
            self.energy += self.growth_rate

    def reproduce(self):
        if self.energy >= 20:  # Arbitrary reproduction threshold
            self.energy -= 10
            return Plant(f"{self.name}-Offspring", self.x, self.y, 10, self.growth_rate)
        return None


class Animal(Entity):
    def __init__(self, name, x, y, energy, speed, food_type):
        super().__init__(name, x, y, energy)
        self.speed = speed
        self.food_type = food_type

    def move(self, max_x, max_y):
        self.x = (self.x + random.randint(-self.speed, self.speed)) % max_x
        self.y = (self.y + random.randint(-self.speed, self.speed)) % max_y

    def eat(self, entities):
        for entity in entities:
            if isinstance(entity, Plant) and self.food_type == "herbivore" and entity.is_alive():
                self.energy += 10
                entity.energy -= 10
                return
            elif isinstance(entity, Animal) and self.food_type == "carnivore" and entity.is_alive():
                self.energy += 20
                entity.alive = False
                return

    def reproduce(self):
        if self.energy >= 30:  # Arbitrary reproduction threshold
            self.energy -= 15
            return Animal(f"{self.name}-Offspring", self.x, self.y, 15, self.speed, self.food_type)
        return None


class Ecosystem:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.entities = []

    def add_entity(self, entity):
        self.entities.append(entity)

    def random_event(self):
        event = random.choice(["drought", "new_species", "disease"])
        if event == "drought":
            print("Drought event! Plants lose energy.")
            for entity in self.entities:
                if isinstance(entity, Plant):
                    entity.energy = max(0, entity.energy - 10)
        elif event == "new_species":
            print("A new species appears!")
            self.add_entity(Animal("NewPredator", random.randint(0, self.width - 1),
                                    random.randint(0, self.height - 1), 30, 2, "carnivore"))
        elif event == "disease":
            print("Disease outbreak! Random animals lose energy.")
            for entity in random.sample(self.entities, len(self.entities) // 4):
                if isinstance(entity, Animal):
                    entity.energy = max(0, entity.energy - 15)

    def simulate_step(self):
        for entity in list(self.entities):  # Use a copy to allow modifications
            if entity.is_alive():
                if isinstance(entity, Plant):
                    entity.act()
                entity.move(self.width, self.height)
                if isinstance(entity, Animal):
                    entity.eat(self.entities)
                    offspring = entity.reproduce()
                    if offspring:
                        self.entities.append(offspring)
            else:
                self.entities.remove(entity)

        if random.random() < 0.2:  # 20% chance of random event
            self.random_event()

    def display(self):
        print("Current Ecosystem State:")
        for entity in self.entities:
            print(entity)

    def generate_report(self):
        plants = sum(1 for e in self.entities if isinstance(e, Plant))
        herbivores = sum(1 for e in self.entities if isinstance(e, Animal) and e.food_type == "herbivore")
        carnivores = sum(1 for e in self.entities if isinstance(e, Animal) and e.food_type == "carnivore")
        print("\nFinal Report:")
        print(f"Plants: {plants}")
        print(f"Herbivores: {herbivores}")
        print(f"Carnivores: {carnivores}")


# User Input Section
def main():
    print("Welcome to the Ecosystem Simulation!")
    width = int(input("Enter the width of the ecosystem: "))
    height = int(input("Enter the height of the ecosystem: "))
    ecosystem = Ecosystem(width, height)

    num_plants = int(input("Enter the number of plants: "))
    for _ in range(num_plants):
        name = input("Enter plant name: ")
        x = random.randint(0, width - 1)
        y = random.randint(0, height - 1)
        energy = int(input(f"Enter energy for {name}: "))
        growth_rate = int(input(f"Enter growth rate for {name}: "))
        ecosystem.add_entity(Plant(name, x, y, energy, growth_rate))

    num_animals = int(input("Enter the number of animals: "))
    for _ in range(num_animals):
        name = input("Enter animal name: ")
        x = random.randint(0, width - 1)
        y = random.randint(0, height - 1)
        energy = int(input(f"Enter energy for {name}: "))
        speed = int(input(f"Enter speed for {name}: "))
        food_type = input(f"Enter food type for {name} (herbivore/carnivore): ").strip().lower()
        ecosystem.add_entity(Animal(name, x, y, energy, speed, food_type))

    num_steps = int(input("Enter the number of simulation steps: "))
    for step in range(num_steps):
        print(f"\nStep {step + 1}:")
        ecosystem.simulate_step()
        ecosystem.display()

    ecosystem.generate_report()


if __name__ == "__main__":
    main()