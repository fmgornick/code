public class Owl {
    String name;
    int age;
    double weight;
    
    public Owl(String newName, int newAge, double newWeight) {
        this.name = newName;
        this.age = newAge;
        this.weight = newWeight;
    }

    public Owl() {}

    public String getName() {
        return name;
    }

    public void setName(String newName) {
        this.name = newName;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int newAge) {
        this.age = newAge;
    }

    public double getWeight() {
        return weight;
    }

    public void setWeight(double newWeight) {
        this.weight = newWeight;
    }

    public boolean equals(Owl other) {
        if (this.name.equals(other.name) && this.age == other.age && this.weight == other.weight) {
            return true;
        }
        else return false;
    }

    public String toString() {
        return "name: " + this.name + "\nage: " + this.age + "\nweight: " + this.weight;
    }


    public static void main(String[] args) {
        Owl a = new Owl("fletcher", 19, 170);
        Owl b = new Owl("steve", 30, 230);
        Owl c = new Owl("fletcher", 19, 170);

        System.out.println("does a = b? " + a.equals(b));
        System.out.println("does a = c? " + a.equals(c));
    }
}
