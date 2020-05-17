# CSCI 1133, Fletcher Gornick, gorni025
# lab Section 002, HW 7


class StudentGrades:
    

    #==========================================
    # Name: __init__
    # Purpose: takes in the input paramaters and initializes them by assigning them 
    # to self
    # Precondition: must atleast be given a student ID
    # Input Parameter(s): 
    # studentID = student's ID
    # lastName = student's last name
    # firstName = student's first name
    # grades = a list of grades from homeworks, quizzes and labs
    # Return Value(s): nothing is returned, just sets up the variables to be used by 
    # the rest of the functions in the class
    #============================================

    def __init__(self, studentID, lastName='', firstName='', grades=[[],[],[]]):
        self.studentID = studentID
        self.lastName = lastName
        self.firstName = firstName
        self.grades = grades
    

    #==========================================
    # Name: setLastName
    # Purpose: takes in an string argument and gives the self.lastName variable the new 
    # attribute
    # Precondition: Input must be a string
    # Input Parameter(s): newLastName = a string indicating the student's new last name
    # Return Value(s): nothing is returned, just reassigns the self.lastName variable
    #============================================
    
    def setLastName(self, newLastName):
        self.lastName = newLastName
    

    #==========================================
    # Name: setFirstName
    # Purpose: takes in an string argument and gives the self.FirstName variable the new 
    # attribute
    # Precondition: Input must be a string
    # Input Parameter(s): newFirstName = a string indicating the student's new first name
    # Return Value(s): nothing is returned, just reassigns the self.FirstName variable
    #============================================
    
    def setFirstName(self, newFirstName):
        self.firstName = newFirstName


    #==========================================
    # Name: getStudentID
    # Purpose: returns the variable self.studentID
    # Precondition: none, function just runs when called
    # Input Parameter(s): none
    # Return Value(s): returns self.studentID variable
    #============================================
    
    def getStudentID(self):
        return str(self.studentID)


    #==========================================
    # Name: getLastName
    # Purpose: returns the variable self.lastName
    # Precondition: none, function just runs when called
    # Input Parameter(s): none
    # Return Value(s): returns self.lastName variable
    #============================================
    
    def getLastName(self):
        return str(self.lastName)
    

    #==========================================
    # Name: getFirstName
    # Purpose: returns the variable self.firstName
    # Precondition: none, function just runs when called
    # Input Parameter(s): none
    # Return Value(s): returns self.firstName variable
    #============================================

    def getFirstName(self):
        return str(self.firstName)


    #==========================================
    # Name: getGrades
    # Purpose: returns the variable self.grades
    # Precondition: none, function just runs when called
    # Input Parameter(s): none
    # Return Value(s): returns self.grades variable
    #============================================
    
    def getGrades(self):
        return str(self.grades)


    #==========================================
    # Name: addGrade
    # Purpose: takes in a score input, adds that score to one of the lists in self.grades
    # depending on second input parameter that must be either a 'Q', 'H', or 'L'
    # Precondition: must input a score and either a 'Q', 'H', or 'L'
    # Input Parameter(s): 
    # score = integer (should be between 1 and 100, but will still run with numbers outside
    # that range)
    # QHL = one character string (either a 'Q', 'H', or 'L')
    # Return Value(s): nothing is returned unless the second input parameter is wrong
    #============================================
    
    def addGrade(self, score, QHL):
        if QHL == 'Q':
            self.grades[0].append(score)
        elif QHL == 'H':
            self.grades[1].append(score)
        elif QHL == 'L':
            self.grades[2].append(score)
        else:
            return 'must be an Q, H, or L in the second parameter argument'


    #==========================================
    # Name: averageGrades
    # Purpose: goes through each list (quizzes, homeworks, and labs), and returns a new list
    # containing the averages of each list
    # Precondition: none, runs without inputs
    # Input Parameter(s): none
    # Return Value(s): a list containing the average of the students quizzes, labs and 
    # homeworks
    #============================================

    def averageGrades(self):

        average_list = []
        for i in range(len(self.grades)):
            sum = 0
            for j in range(len(self.grades[i])):
                sum += self.grades[i][j]
            average_list.append(round(sum/len(self.grades[i])))
        
        return average_list


    #==========================================
    # Name: __str__
    # Purpose: takes all the useful data and presents it in a way the user can read easier
    # Precondition: none, should just run
    # Input Parameter(s): none
    # Return Value(s): few lines listing the student's ID, grades, and Quiz / Homework / Lab 
    # averages
    #============================================
    
    def __str__(self):
        return 'ID: ' + str(self.studentID) + '\nGrades: ' + str(self.grades) + '\nAverages: ' + str(self.averageGrades())




class CourseGrades(StudentGrades):


    #==========================================
    # Name: __init__
    # Purpose: takes in the input paramaters and initializes them by assigning them 
    # to self
    # Precondition: must be given the course name, section, semester, and year
    # Input Parameter(s): 
    # course = the course
    # section = course's section
    # semester = semester the course takes place
    # year = year the course takes place
    # grades = a list of the StudentGrades class objects, although it starts off empty, and
    # you must use the addStudent function to append to the list
    # Return Value(s): nothing is returned, just sets up the variables to be used by 
    # the rest of the functions in the class
    #============================================

    def __init__(self, course, section, semester, year, grades=[]):
        self.course = course
        self.section = section
        self.semester = semester
        self.year = year
        self.grades = grades


    #==========================================
    # Name: getGrades
    # Purpose: returns the variable self.grades, which contains a list of StudentGrades
    # objects
    # Precondition: none, function just runs when called
    # Input Parameter(s): none
    # Return Value(s): returns self.grades variable
    #============================================
    
    def getGrades(self):
        return self.grades
    

    #==========================================
    # Name: printStudents
    # Purpose: loops through self.grads and prints the StudentGrades objects
    # Precondition: none, function just runs when called
    # Input Parameter(s): none
    # Return Value(s): nothing is returned but it does print the self.grades variable
    #============================================
    
    def printStudents(self):
        for i in self.grades:
            print(i)


    #==========================================
    # Name: averages
    # Purpose: goes through the list self.grades, and averages out every score of each 
    # student returning each student's average as a list
    # Precondition: none, runs without inputs
    # Input Parameter(s): none
    # Return Value(s): a list containing the average of all scores by each student
    #============================================
    
    def averages(self):

        average_list = []

        if self.grades == []:
            return 'no students added yet'

        else:

            for i in range(len(self.grades)):
                sum = 0
                number = 0

                for j in range(len(self.grades[i][3])):

                    for k in range(len(self.grades[i][3][j])):
                        sum += self.grades[i][3][j][k]
                        number += 1

                average_list.append(round(sum/number))
        
        return average_list
    

    #==========================================
    # Name: addStudent
    # Purpose: takes in an object of type StudentGrades, and adds it to the self.grades
    # list
    # Precondition: student must be of datatype 'StudentGrades'
    # Input Parameter(s): student = a 'Student Grades' type containin it's arguments
    # (studentID, lastName, firstName, grades)
    # Return Value(s): nothing is returned, but a list containing student.studentID, 
    # student.lastName, student.firstName, and student.grades is appended to self.grades
    #============================================
    
    def addStudent(self, student):
        self.grades.append([student.studentID, student.lastName, student.firstName, student.grades])
    

    #==========================================
    # Name: __str__
    # Purpose: takes all the useful data and presents it in a way the user can read easier
    # Precondition: none, should just run
    # Input Parameter(s): none
    # Return Value(s): one line containing the course, section, semester, year, and a list
    # of all student's average grades
    #============================================

    def __str__(self):
        return str(self.course) + ', ' + str(self.section) + ', ' + str(self.semester) + ', ' + str(self.year) + ', ' + str(self.averages())






if __name__ == '__main__':
    agrades = StudentGrades(5579904, 'Gornick', 'Fletcher', [[87,23,45,90,96],[32,65,78,80,56],[12,43,99,87,100]])
    bgrades = StudentGrades(4239012, 'Doe', 'John', [[45,63,90,89,76],[78,65,33,12,87],[90,94,65,78,88]])
    cgrades = StudentGrades(9930571, 'Deer', 'Jane', [[23,55,49,89,70],[12,60,98,60,80],[44,79,56,60,79]])

    course = CourseGrades('CSCI 1133', '002','Spring', 2020)
    course.addStudent(agrades)
    course.addStudent(bgrades)
    course.addStudent(cgrades)
    print(course)
    print(course.getGrades())
    print(agrades.getGrades())

