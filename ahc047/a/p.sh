#!/bin/bash

# Ensure the output directory exists
mkdir -p out
g main.cpp

# Loop from 0 to 10
for i in $(seq 0 9); do
    # Format the number to be 4 digits with leading zeros (e.g., 0000, 0001, ..., 0010)
    padded_number=$(printf "%04d" "$i")

    input_file="in/${padded_number}.txt"
    output_file="out/${padded_number}.txt"

    echo "Running ./a.out with input ${input_file} and saving output to ${output_file}"

    # Execute ./a.out with the input file and redirect stdout to the output file
    # Check if the input file actually exists before trying to execute
    if [ -f "${input_file}" ]; then
        ./a.out < "${input_file}" > "${output_file}"

        # Check if the execution was successful
        if [ $? -ne 0 ]; then
            echo "Error running ./a.out with ${input_file}"
        fi
    else
        echo "Error: Input file ${input_file} does not exist."
    fi
done

echo "Script finished."
