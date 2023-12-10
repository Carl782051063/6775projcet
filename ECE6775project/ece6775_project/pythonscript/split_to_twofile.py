# Define the two filenames
output_file_col1 = 'column1.txt'
output_file_col2 = 'column2.txt'

# Open the input file and output files
with open('data.txt', 'r') as input_file, \
     open(output_file_col1, 'w') as output_file1, \
     open(output_file_col2, 'w') as output_file2:

    # Read the input file line by line
    for line in input_file:
        # Split each line by space
        columns = line.split()
        if len(columns) >= 2:
            # Extract data from the first and second columns
            col1 = columns[0]
            col2 = columns[1]

            # Write the data to the respective output files
            output_file1.write(col1 + '\n')
            output_file2.write(col2 + '\n')
