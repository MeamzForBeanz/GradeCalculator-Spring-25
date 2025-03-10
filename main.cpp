#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm> // New: Include the algorithm header

int main()
{
    int total_course_points = 0;
    float assignment_score = 0.00;
    float total_points_earned = 0.00;
    float total_percentage_earned = 0.00;
    float A_points = 0.00, B_points = 0.00, C_points = 0.00, D_points = 0.00;
    float A_percentage = 0.00, B_percentage = 0.00, C_percentage = 0.00, D_percentage = 0.00;
    char earned_grade;
    std::vector<float> assignment_scores;
//Greeting
    std::cout << "Welcome to Charlie Brown's Grade Calculator for COSC 1436\n\n";
std::cout << "Grading Scheme\n";
std::cout << "Please input the Total Points Possible: ";
std::cin >> total_course_points;
std::cout << '\n';
    for (char grade = 'A'; grade <= 'D'; grade++)
    {
        std::cout << "Please input the Minimum Points for a '" << grade << "': ";
        if (grade == 'A')
            std::cin >> A_points;
        else if (grade == 'B')
            std::cin >> B_points;
        else if (grade == 'C')
            std::cin >> C_points;
        else if (grade == 'D')
            std::cin >> D_points;
        std::cout << '\n';
    }

    A_percentage = (A_points / total_course_points) * 100;
    B_percentage = (B_points / total_course_points) * 100;
    C_percentage = (C_points / total_course_points) * 100;
    D_percentage = (D_points / total_course_points) * 100;
    std::cout << "The Grading Scheme You Input\n";
    std::cout << "Total Points Possible in the Course: " << total_course_points << '\n';
    std::cout << "Points needed for an 'A': " << A_points << " or " << A_percentage << '%' << '\n';
    std::cout << "Points needed for a 'B': " << B_points << " or " << B_percentage << '%' << '\n';
    std::cout << "Points needed for a 'C': " << C_points << " or " << C_percentage << '%' << '\n';
    std::cout << "Points needed for a 'D': " << D_points << " or " << D_percentage << '%' << "\n\n";

    std::cout << "Grade Calculation\n";
    std::cout << "You will be prompted to input scores for all assignments.\n"
              << "(Input a negative number to cease input and calculate letter grade.)\n\n";
    bool score_input = true;
    int assignment = 1;
    do
    {
        std::cout << "Please input the points earned for Assignment " << assignment << ": ";
        std::cin >> assignment_score;
        if (assignment_score >= 0)
        {
            assignment_scores.push_back(assignment_score); // Add the score to the vector
            total_points_earned += assignment_score;
            assignment++;
        }
        else
        {
            score_input = false;
            continue;
        }
    } while (score_input);

    // Find the highest and lowest scores
    if (!assignment_scores.empty())
    {
        auto min_it = std::min_element(assignment_scores.begin(), assignment_scores.end());
        auto max_it = std::max_element(assignment_scores.begin(), assignment_scores.end());
        std::cout << "\nHighest score: " << *max_it << '\n';
        std::cout << "Lowest score: " << *min_it << '\n';
    }
    else
    {
        std::cout << "\nNo scores were entered.\n";
    }

    if (total_points_earned >= A_points)
        earned_grade = 'A';
    else if (total_points_earned >= B_points)
        earned_grade = 'B';
    else if (total_points_earned >= C_points)
        earned_grade = 'C';
    else if (total_points_earned >= D_points)
        earned_grade = 'D';
    else
        earned_grade = 'F';
    total_percentage_earned = (total_points_earned / total_course_points) * 100;

    std::cout << "Total Points Earned: " << total_points_earned << '\n'
              << "Total Points Possible: " << total_course_points << '\n'
              << "Total Percentage: " << total_percentage_earned << '%' << '\n'
              << "Total Percentage (rounded): " << round(total_percentage_earned) << '%' << '\n'
              << "Final Letter Grade: " << earned_grade << '\n';
    return 0;
}