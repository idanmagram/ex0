/**************************************************************************
 * filename:    part1.c
 * brief:       Reading numbers and checking if the numbers
 *              are power of 2.
 * author:      Idan Magram
 * ID number:   318735156
 * date:        1.4.22
**************************************************************************/

/** Headers **************************************************************/
#include <stdio.h>
#include <stdlib.h>

/** Enums ****************************************************************/
enum exit_status {
    STATUS_SUCCESS,
    STATUS_FAILURE,
    STATUS_PART1_MAIN_SCAN_NUMBER_FAILED,
    STATUS_PART1_MAIN_SCAN_LAST_CHAR_FAILED,
    STATUS_PART1_POWER_OF_NUMBER_INVALID_PARAMS,
    STATUS_PART1_GETTING_INPUT_INVALID_PARAMS,
    STATUS_PART1_GETTING_INPUT_SCAN_SIZE_FAIlED,
    STATUS_PART1_MAIN_ARRAY_ALLOCATION_FAILED,
    STATUS_PART1_MAIN_GETTING_SIZE_INPUT_FAILED,
};
enum bool {
    FALSE,
    TRUE
};

/** Functions *************************************************************/
/**************************************************************************
 * Function:    getting_size_input
 * @brief       Getting the size input from the user
 * @params      size_input(out): amount of numbers
 * @return      status
**************************************************************************/
enum exit_status
getting_size_input(int* size_input);


/**************************************************************************
 * Function:    power_of_number
 * @brief       Checking if a number is a power of 2
 * @params      number(in): input number
 *              power(out): log2 of number
 *              is_power(out): True if number is a power of 2
 * @return      status
**************************************************************************/
enum exit_status
power_of_number(int number,
                int *power,
                enum bool* is_power);


/**************************************************************************
 * Function:    main
 * @brief       Reading numbers and checking if the numbers
 *              are power of 2.
 * @return      exit status
**************************************************************************/
int main()
{
    enum exit_status status = STATUS_FAILURE;
    enum bool is_power = FALSE;
    int* arr = NULL;
    int size_input = 0;
    int number;
    int power = 0;
    int power_sum = 0;
    int i = 0;
    int libc_retval = 0;
    char last_char = 0;

    /* Scan amount of numbers */
    status = getting_size_input(&size_input);
    if (status != STATUS_SUCCESS) {
        status = STATUS_PART1_MAIN_GETTING_SIZE_INPUT_FAILED;
        (void) printf("Invalid size\n");
        goto cleanup;
    }
    if (0 >= size_input) {
        goto cleanup;
    }

    arr = (int*) malloc(size_input * sizeof(int));
    if (NULL == arr) {
        status = STATUS_PART1_MAIN_ARRAY_ALLOCATION_FAILED;
        goto cleanup;
    }

    /* Scan numbers */
    (void) printf("Enter numbers:\n");
    do {
        libc_retval = scanf("%d", &number);
        if (1 > libc_retval) {
            (void) printf("Invalid number\n");
            status = STATUS_PART1_MAIN_SCAN_NUMBER_FAILED;
            goto cleanup;
        } else {
            arr[i] = number;
        }
        i++;
    } while (i < size_input);

    /* Fix edge case, last number is invalid */
    last_char = (char) getchar();
    if (last_char != ' ' && last_char != EOF && last_char != '\n' && last_char != '\t') {
        (void) printf("Invalid number\n");
        status = STATUS_PART1_MAIN_SCAN_LAST_CHAR_FAILED;
        goto cleanup;
    }

    /* Calculate and sum log2 of the numbers which are a power of 2 */
    for (i = 0; i < size_input; i++) {
        status = power_of_number(arr[i], &power, &is_power);
        if (status != STATUS_SUCCESS) {
            goto cleanup;
        }
        else if (TRUE == is_power) {
            power_sum += power;
            (void) printf("The number %d is a power of 2: %d = 2^%d\n", arr[i], arr[i], power);
        }
    }

    (void) printf("Total exponent sum is %d\n", power_sum);
    status = STATUS_SUCCESS;

cleanup:
    if ((STATUS_PART1_MAIN_GETTING_SIZE_INPUT_FAILED != status) &&
        (STATUS_PART1_MAIN_ARRAY_ALLOCATION_FAILED != status)) {
        (void) free(arr);
    }
    /* return (int) status; */
    return 0; /* As requested in ex0 */
}

/**************************************************************************
 * Function:    getting_size_input
**************************************************************************/
enum exit_status getting_size_input(int* size_input)
{
    enum exit_status status = STATUS_FAILURE;
    int libc_retval = 0;
    int size_input_local = 0;

    /* Parameters check */
    if (NULL == size_input) {
        status = STATUS_PART1_GETTING_INPUT_INVALID_PARAMS;
        goto cleanup;
    }

    /* Scan amount of numbers */
    (void) printf("Enter size of input:\n");
    libc_retval = scanf("%d", &size_input_local);
    if (1 > libc_retval) {
        status = STATUS_PART1_GETTING_INPUT_SCAN_SIZE_FAIlED;
        goto cleanup;
    }

    if(0 >= size_input_local) {
        (void) printf("Invalid size\n");
    }
    *size_input = size_input_local;
    status = STATUS_SUCCESS;
cleanup:
    return status;

}

/**************************************************************************
 * Function:    power_of_number
**************************************************************************/
enum exit_status
power_of_number(int number,
                int *power,
                enum bool* is_power) {
    enum exit_status status = STATUS_FAILURE;
    double division = 0;
    int power_local = 0;

    /* Parameters check */
    if ((NULL == power) || (NULL == is_power)) {
        status = STATUS_PART1_POWER_OF_NUMBER_INVALID_PARAMS;
        goto cleanup;
    }

    /* Calculating log 2 of number */
    division = (double)(number);
    while (1 < division) {
        division /= 2;
        power_local++;
    }
    if (division == 1) {
        *is_power = TRUE;
    } else {
        *is_power = FALSE;
    }

    *power = power_local;
    status = STATUS_SUCCESS;
cleanup:
    return (int) status;
}