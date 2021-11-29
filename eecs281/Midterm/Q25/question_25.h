/*
 * Starter file for:
 *   F21, Midterm Exam, Question 25
 *
 * Do not try to submit this file to the autograder!
 * Upload it to Gradescope:
 *   [F21] Midterm Question 25
 *
 * Before uploading, as you "browse" for the file, check the last modified time!
 * It should be when you last saved the file.
 * Make sure you are uploading a file named question_25.h
 */

#pragma once

// DO NOT MODIFY ANYTHING ABOVE THIS LINE!

// You may not include anything, or use anything from the STL.

template <class ForwardIterator, class OutputIterator, class Predicate>
OutputIterator question_25(ForwardIterator first, ForwardIterator last,
                           OutputIterator result, Predicate pred) {
    // TODO: write this function
    while(first != last){
        if(!pred(*first)){
            *result = *first;
            ++result;
        }
        ++first;
    }
    return result;
} // question_25()
