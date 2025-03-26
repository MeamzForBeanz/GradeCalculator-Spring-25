#include "grade_calculator.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>

GradeCalculator::GradeCalculator()
    : total_course_points(0), total_points_earned(0.0f),
      total_percentage_earned(0.0f), A_points(0.0f), B_points(0.0f),
      C_points(0.0f), D_points(0.0f), A_percentage(0.0f), B_percentage(0.0f),
      C_percentage(0.0f), D_percentage(0.0f), earned_grade('F') {}

void GradeCalculator::setGradingScheme(int total_course_points, float A_points, float B_points, float C_points, float D_points) {
  this->total_course_points = total_course_points;
  this->A_points = A_points;
  this->B_points = B_points;
  this->C_points = C_points;
  this->D_points = D_points;
  A_percentage = (A_points / total_course_points) * 100;
  B_percentage = (B_points / total_course_points) * 100;
  C_percentage = (C_points / total_course_points) * 100;
  D_percentage = (D_points / total_course_points) * 100;
}

void GradeCalculator::inputAssignments() {
  bool score_input = true;
  std::string assignment_name;
  float assignment_score;
  float assignment_possible;
  bool assignment_bonus;
  std::cout << "Grade Calculation\n";
  std::cout << "You will be prompted to input scores for all assignments. \n"
            << "(Input 'done' or 'Done' to cease input and calculate the "
               "letter grade.) \n \n";
  do {
    std::cout << "Please input the assignment name or 'done' to quit: ";
    std::getline(std::cin >> std::ws, assignment_name);
    if (assignment_name != "done" && assignment_name != "Done") {
      Assignment assignment;
      assignment.setName(assignment_name);
      std::cout << "Please input the points possible for " << assignment_name
                << ": ";
      std::cin >> assignment_possible;
      while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid numeric value for "
                     "points possible: ";
        std::cout << "Invalid input. Please enter a valid numeric value for "
                     "points possible: ";
        std::cin >> assignment_possible;
      }
      assignment.setPointsPossible(assignment_possible);
      std::cout << "Please input the points earned for " << assignment_name
                << ": ";
      std::cin >> assignment_score;
      while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid numeric score for " << assignment_name << ": ";
               std::cin >>
            assignment_score;
      }
      assignment.setPointsEarned(assignment_score);
      std::cout << "Is this a bonus assignment? (1 for Yes, 0 for No): ";
      std::cin >> assignment_bonus;
      while (std::cin.fail() ||
             (assignment_bonus != 0 && assignment_bonus != 1)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter 1 (Yes) or 0 (No): ";
        std::cin >> assignment_bonus;
      }
      assignment.setBonus(assignment_bonus);
      assignments.push_back(assignment);
      total_points_earned += assignment_score;
    } else {
      score_input = false;
    }
  } while (score_input);
}
void GradeCalculator::calculateGrade() {
  if (total_points_earned >= A_points) {
    earned_grade = 'A';
  } else if (total_points_earned >= B_points) {
    earned_grade = 'B';
  } else if (total_points_earned >= C_points) {
    earned_grade = 'C';
  } else if (total_points_earned >= D_points) {
    earned_grade = 'D';
  } else {
    earned_grade = 'F';
  }
  total_percentage_earned = (total_points_earned / total_course_points) * 100;
}

void GradeCalculator::displayResults() const {
  std::cout << "The Grading Scheme You Input\n";
  std::cout << "Total Points Possible in the Course: " << total_course_points
            << '\n';
  std::cout << "Points needed for an 'A': " << A_points << " or "
            << A_percentage << '%' << '\n';
  std::cout << "Points needed for a 'B': " << B_points << " or " << B_percentage
            << '%' << '\n';
  std::cout << "Points needed for a 'C': " << C_points << " or " << C_percentage
            << '%' << '\n';
  std::cout << "Points needed for a 'D': " << D_points << " or " << D_percentage
            << '%' << "\n \n";
  std::cout << "\nScores entered:\n";
  if (!assignments.empty()) {
    for (const auto &assignment : assignments) {
      float percentage =
          (assignment.getPointsEarned() / assignment.getPointsPossible()) * 100;
      std::cout << "Assignment: " << assignment.getName()
                << ", Points Earned: " << assignment.getPointsEarned()
                << ", Points Possible: " << assignment.getPointsPossible()
                << ", Percentage: " << percentage << '%'
                << ", Bonus: " << (assignment.isBonus() ? "Yes" : "No") << '\n';
    }
    auto min_it =
        std::min_element(assignments.begin(), assignments.end(),
                         [](const Assignment &a, const Assignment &b) {
                           return a.getPointsEarned() < b.getPointsEarned();
                         });
    auto max_it =
        std::max_element(assignments.begin(), assignments.end(),
                         [](const Assignment &a, const Assignment &b) {
                           return a.getPointsEarned() < b.getPointsEarned();
                         });
    std::cout << "\nHighest score: " << max_it->getPointsEarned() << '\n';
    std::cout << "Lowest score: " << min_it->getPointsEarned() << '\n';
  } else {
    std::cout << "\nNo scores were entered.\n";
  }
  std::cout << "Total Points Earned: " << total_points_earned
            << "\nTotal Points Possible: " << total_course_points
            << "\nTotal Percentage: " << total_percentage_earned << '%'
            << "\nTotal Percentage (rounded): "
            << round(total_percentage_earned) << '%'
            << "\nFinal Letter Grade: " << earned_grade;
}