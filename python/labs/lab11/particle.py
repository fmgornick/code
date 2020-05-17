class particle:

    def __init__(self, mass=0, position=[0,0,0], velocity=[0,0,0]):
        self.mass = mass
        self.position = position
        self.velocity = velocity
    
    def __str__(self):
        return 'mass: ' + str(self.mass) + '\nposition: ' + str(self.position) + '\nvelocity: ' + str(self.velocity)

    def setMass(self, m):
        self.mass = m
    
    def momentum(self):
        for i in range(len(self.velocity)):
            self.velocity[i] *= self.mass
        return self.velocity

    def accelerate(self, a, t):

        new_position = []
        new_velocity = []

        for i in range(len(self.position)):

            new_position.append(self.position[i] + self.velocity[i] * t + 0.5 * a * t**2)
            new_velocity.append(self.velocity[i] + a * t)

        return particle(self.mass, new_position, new_velocity)

