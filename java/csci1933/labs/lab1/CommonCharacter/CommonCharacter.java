// found how to iterate through a map and find that greatest key value pair on https://www.baeldung.com/java-find-map-max
// found out how to declare and use a map on https://www.educative.io/edpresso/how-to-create-a-dictionary-in-java
// found out what the map.entrySet() command does on https://www.geeksforgeeks.org/hashmap-entryset-method-in-java/

import java.util.*;

public class CommonCharacter {
    public static void main(String args[]) {

        Scanner object = new Scanner(System.in);
        HashMap<Character, Integer> letterOccurences = new HashMap<Character, Integer>();
        Map.Entry<Character, Integer> maxOccurence = null;

        System.out.print("Enter String: ");

        String sentence = object.nextLine();
        
        for (int i = 0; i < sentence.length() ; ++i) {
            if (letterOccurences.containsKey(sentence.charAt(i))) {
                letterOccurences.put(sentence.charAt(i), letterOccurences.get(sentence.charAt(i)) + 1);    
            }

            else letterOccurences.put(sentence.charAt(i), 1);
        }

        //   defines key value pair types  iterator    map          key value pairs
        for (Map.Entry<Character, Integer> entry : letterOccurences.entrySet()) {
            if (maxOccurence == null) {
                maxOccurence = entry;
            }

        //   if letterOccurences key value pair greater than max, then change max
            else if (entry.getValue().compareTo(maxOccurence.getValue()) > 0) {
                maxOccurence = entry;
            }
        }

        System.out.println(maxOccurence);
    }
}
