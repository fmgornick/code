/*! \page tests_description Tests Overview
 *
 * \section Testing Overview
 *
 * The tests are what allow us to check the accuracy of our code, without tests
 * we would not be able to find different issues in our code- simply relying on
 * a successful compile is both ignorant and silly. We use a combination of unit
 * tests, component tests, integration tests, and regression tests to test the
 * accuracy of our code.
 *
 * Unit tests test one unit at a time, allowing us to easily determine when
 * something specific is going wrong in a specific piece of code. Unit tests
 * are super useful in the beginning stage of your testing process, when you
 * are writing a new 'unit' of code you use various unit tests to test whether
 * your code is acting as you would expect it to.
 *
 * Component tests are virtually identical in nature to unit tests but they
 * use real data rather than made up or "dummy" data to test code. Component
 * tests are used in the second stage of your testing process, using real data
 * more accurately shows how a piece of code will interact with your program
 * and gives you a better image of how your code is really working.
 *
 * Integration tests check to see if multiple units work together in tandem-
 * they basically make sure nothing breaks when you combine certain units
 * together. Integration tests are the third step in the testing progess, you
 * must test whether your new addition into your program doesn't break your
 * existing pieces of code.
 *
 * Regression tests check if certain changes to existing code have caused issues
 * with anything else anywhere else within the code by testing it against known
 * scenarios. Regression tests basically test if the units have been integrated
 * correctly. Regression tests are the last step in the testing progress, these
 * tests basically mimic how your code will run all together as a whole.
 *
 * Together, these tests provide an exhaustive look into how our code looks both
 * as single parts on their own and each of these individual parts working
 * together to form a whole. Without these tests, you could find bugs when using
 * the code later on and without tests it would be far more difficult to find
 * where exactly an issue is happening. Especially in the case where the issue
 * lies not in a certain piece of code but rather in where pieces of code are
 * working together. Thoughtful testing also helps in the extendability of this
 * project, these tests can provide a helpful template for writing new tests in
 * the future and can also be useful for people looking at the code and trying
 * to figure out how to show what it is doing or run commands.
 *
 * Ultimately, while I hope what I have written above has shown this I want to
 * clearly state- TESTING IS SUPER IMPORTANT. Having good and all-encompassing
 * tests is an integral part of the coding process and helped us greatly in this
 * project to see how each of our individual pieces (units) of code worked
 * alongside each others.
 *
 */
