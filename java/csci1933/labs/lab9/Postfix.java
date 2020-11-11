public class Postfix {
    public static double evaluate(String[] expression) throws StackException {
        Stack<Double> stack = new Stack<Double>();
        for (String s : expression) {
            if (s.equals("+")) {
                double num1 = stack.pop();
                double num2 = stack.pop();
                stack.push(num2 + num1);
            }

            else if (s.equals("-")) {
                double num1 = stack.pop();
                double num2 = stack.pop();
                stack.push(num2 - num1);
            }

            else if (s.equals("*")) {
                double num1 = stack.pop();
                double num2 = stack.pop();
                stack.push(num2 * num1);
            }

            else if (s.equals("/")) {
                double num1 = stack.pop();
                double num2 = stack.pop();
                stack.push(num2 / num1);
            }

            else {
                stack.push(Double.parseDouble(s));
            }
        }
        return stack.pop();
    }
    public static void main (String[] args) throws StackException {
        String[] exp1 = {"1","2","+","3","4","+","/"};
        String[] exp2 = {"1","2","7","3","4","8","10"};

        try {
            System.out.println(Postfix.evaluate(exp1));
            System.out.println(Postfix.evaluate(exp2));
        }

        catch (StackException e) {
            System.out.println("error, stack size: " + e.getSize());
        }

        finally {
            System.out.println("Evaluation Complete");
        }
    }
}
