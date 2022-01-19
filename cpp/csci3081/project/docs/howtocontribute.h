/*! \page how_to_contribute How to Contribute
 *
 * \section adding_a_feature Adding a Feature
 *
 * Once you've decided upon a feature you'd like to add, navigate to the team GitHub page. From there, click on the "Issues" tab.
 * In the "Issues" page, click on the "New Issue" Button and fill the title with the relevant name and bracketed GitHub key with point value.
 * Then, fill in the description with any additional necessary information, assign the issue to a group member, and update the issue with any 
 * "Project" or "Milestone" tags if applicable. Finally, click the "Submit New Issue" button to create the issue.
 *
 * \section creating_a_local_branch Creating a Local Branch
 * Once the issue has been created, you can now create the branch that you will develop the feature on. It's important to maintain good source
 * source control and ensure that working versions of code are not overwritten by dysfunctional code that's still under development. The easiest
 * way to create the branch is through the terminal. In your terminal, navigate to your cloned version of the repository. Run the command 
 * "git status" to verify which branch you're currently on. If you're not currently on 'develop', stash or commit any changes you've made to your 
 * branch, and then use "git checkout develop" to switch to the 'develop' branch. Then, enter "git pull" to ensure you're working on the 
 * most up-to-date version of the 'develop' code. Finally, enter "git checkout -b 'your issue name here'" to create the new branch.
 * 
 * \section coding_principles Coding Principles 
 * Now that you've created a new branch, it's imporant to follow principled coding standards. Be sure to be consistent with the naming conventions
 * established across the code base. Make sure to leave clear comments in the class and header files that you write. It is important that
 * memory is being properly managed, so check that your programs are free of memory leaks with Valgrind. Be sure to use the 'Big Three' of 
 * the copy constructor, destructor, and assignment operator. Object oriented programming is important for this project, so be sure to 
 * follow procedure with encapsulation, as well as inheritance and polymorphism, which feature prominently in the code. 
 * It is expected that you follow SOLID design principles, i.e. Single Responsibility for classes, Open/Closed Principle, etc. 
 * Also, follow safe coding practices by using const references and methods when possible, and be sure to keep interfaces separated.
 * 
 * \section pull_requests Pull Requests and Code Review
 * Finally, when you have the added functionality running correctly and without memory leaks on your local machine, use 'git commit' and
 * 'git push' to push your code to the upstream branch. Then, create pull request, requesting to merge your branch into develop. When creating 
 * the pull request, make the name of the pull request the same as the issue that you're working on. Write a short description describing
 * the changes and what's been added, and include the #tag that corresponds to the issue. Request review from one or more other developers, and
 * then submit the request. The review process of the pull request is carried out by a teammate, who goes through the changed files, verifying
 * that the they've viewed the changes and that said changes appear to follow the coding principles in the above section, as well as that the 
 * changes appear to accomplish what the created issue states. Comments will be left in any areas of significance or concern, and depending on  
 * whether or not the code is ready for deployment, the request will either be approved and merged, or closed. Should the request be closed,
 * the developer will address comments left in the review, and make changes and do further testing on the local branch before starting the 
 * pull request and review process over again.
 *
 *
 */