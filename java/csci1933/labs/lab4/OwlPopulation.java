import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class OwlPopulation {
    private String fileName;
    private Owl[] data;


    public int populateData() throws FileNotFoundException{
        File f = new File(fileName);
        Scanner scanner = new Scanner(f);

        int numLines = 0;
        while(scanner.hasNextLine()){
            numLines++;
            String s = scanner.nextLine();
        }
        scanner.close();

        data = new Owl[numLines];   //data is is allocated the exact amount of space it needs
        scanner = new Scanner(f);

        int i = 0;
        while(scanner.hasNextLine()) {
            String[] input = scanner.nextLine().split(",");
            data[i] = new Owl(input[0], Integer.parseInt(input[1]), Double.parseDouble(input[2]));

            i++;
        }

        return data.length;
    }

    public OwlPopulation(String fileName) throws FileNotFoundException{
        this.fileName = fileName;
        populateData();
    }

    public double averageAge(){
        double sum = 0;
        for (int i = 0; i < data.length; i++) {
            sum += data[i].getAge();
        }
        return sum / data.length;
    }

    public Owl getYoungest(){
        Owl youngest = data[0];
        for (int i = 1; i < data.length; i++) {
            if (data[i].getAge() < youngest.getAge()) youngest = data[i];
        }
        return youngest;
    }

    public Owl getHeaviest(){
        Owl heaviest = data[0];
        for (int i = 1; i < data.length; i++) {
            if (data[i].getWeight() > heaviest.getWeight()) heaviest = data[i];
        }
        return heaviest;
    }

    public String toString(){
        return "\nyoungest owl: " + getYoungest().getName() + ", age: " + getYoungest().getAge()
            + "\nheaviest owl: " + getHeaviest().getName() + ", age: " + getHeaviest().getAge()
            + "\naverage age of owls: " + String.format("%.2f", averageAge());
    }

    public boolean containsOwl(Owl other) {
        for (int i = 0; i < data.length; i++) {
            if (data[i].equals(other)) return true;
        }
        return false;
    }

    public void merge(OwlPopulation other){
        int extra = 0;
        for (int i = 0; i < other.data.length; i++) {
            if (!containsOwl(other.data[i])) extra++;
        }

        Owl[] newArray = new Owl[data.length + extra];
        for (int j = 0; j < data.length; j++) {
            newArray[j] = data[j];
        }

        int l = 0;
        for (int k = 0; k < other.data.length; k++) {
            if (!containsOwl(other.data[k])) {
                newArray[data.length + l] = other.data[k];
                l++;
            }
        }

        data = newArray;
    }

    public int popSize(){
        return data.length;
    }

    public static void main(String[] args) {
        try {

            //The following should run when you are complete. Feel free to comment out as you see fit while you work.
            OwlPopulation pop1 = new OwlPopulation("owlPopulation1.csv");
            System.out.println(pop1);
            System.out.println("population size: " + pop1.popSize());

            OwlPopulation pop2 = new OwlPopulation("owlPopulation2.csv");
            System.out.println(pop2);
            System.out.println("population size: " + pop2.popSize());

            pop1.merge(pop2);
            System.out.println(pop1);
            System.out.println("population size: " + pop1.popSize());

        }
        catch (FileNotFoundException f){
            System.out.println("File not found.");
        }
    }


}
