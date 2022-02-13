# Force Remove output file and exe if exist
rm -rf output

## Clear terminal
clear

# Run the executable
./runner input output

# Compare the input and output
cmp --silent input output && echo '### SUCCESS: Files Are Identical! ###' || echo '### WARNING: Files Are Different! ###'