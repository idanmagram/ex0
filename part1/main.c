/**************************************************************************
 * filename:    hw0part1.c
 * brief:       Reading numbers and checking if the numbers
 *              are power of 2.
 * author:      Idan Magram
 * ID number:   318735156
 * date:        1.4.22
**************************************************************************/

/** Headers **************************************************************/
#include <stdio.h>

/** Macros ***************************************************************/

/** Enums ****************************************************************/
enum exit_status {
    STATUS_SUCCESS,
    STATUS_SCANF_FAILED,
    STATUS_FAILURE,
    STATUS_PART1_POWER_OF_NUMBER_INVALID_PARAMS,
    STATUS_PART1_GETTING_INPUT_INVALID_PARAMS,
    STATUS_PART1_GETTING_INPUT_SCAN_SIZE_FAIlED,
    STATUS_PART1_GETTING_INPUT_SIZE_INVALID
};

enum bool {
    FALSE,
    TRUE
};

/** Functions *************************************************************/
enum exit_status
getting_size_input(int* size_input);
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
    enum exit_status status = STATUS_SUCCESS;
    int size_input = 0;
    int number;
    int power = 0;
    int power_sum = 0;
    int i;
    enum bool is_power = FALSE;

    getting_size_input(&size_input);

    for (i = 0; i < size_input; i++)
    {
        printf("Enter numbers:\n");
        if (scanf("%d", &number) < 1)
        {
            status = STATUS_SCANF_FAILED;
            goto cleanup;
        }
        else
        {
            status = power_of_number(number, &power, &is_power);
            if (TRUE == is_power)
            {
                power_sum += power;
                printf("The number %d is a power of 2: %d = 2^%d\n",number, number, power);
            }
        }
    }
    printf("Total exponent sum is %d",power_sum);
cleanup:
    return (int) status;

}

enum exit_status getting_size_input(int* size_input)
{
    enum exit_status status = STATUS_FAILURE;
    int libc_retval = 0;
    int size_input_local = 0;

    if (NULL == size_input) {
        status = STATUS_PART1_GETTING_INPUT_INVALID_PARAMS;
        goto cleanup;
    }

    (void) printf("Enter size of input:\n");
    libc_retval = scanf("%d", &size_input_local);
    if (1 > libc_retval) {
        status = STATUS_PART1_GETTING_INPUT_SCAN_SIZE_FAIlED;
        goto cleanup;
    }

    if(0 >= size_input_local) {
        (void) printf("Invalid size");
        status = STATUS_PART1_GETTING_INPUT_SIZE_INVALID;
        goto cleanup;
    }
    *size_input = size_input_local;
    status = STATUS_SUCCESS;
cleanup:
    return status;

}

enum exit_status
power_of_number(int number,
                int *power,
                enum bool* is_power) {
    enum exit_status status = STATUS_FAILURE;
    double division = 0;
    int power_local = 0;

    if ((0 > number) || (NULL == power) || (NULL == is_power)) {
        status = STATUS_PART1_POWER_OF_NUMBER_INVALID_PARAMS;
        goto cleanup;
    }

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