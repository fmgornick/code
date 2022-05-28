use std::io::{self, Write};

fn main() {
    print!("sentence: ");
    io::stdout().flush().unwrap();

    let mut sentence = String::new();
    io::stdin()
        .read_line(&mut sentence)
        .expect("couldn't read line");

    println!("first word: {}", first_word(&sentence));
    println!("second word: {}", second_word(&sentence));
    println!("word count: {}", wc(&sentence));
}

fn first_word(s: &str) -> &str {
    for (i, c) in s.chars().enumerate() {
        if c == ' ' {
            return &s[..i];
        }
    }
    &s
}

fn second_word(s: &str) -> &str {
    let mut start: usize = 0;
    for (i, c) in s.chars().enumerate() {
        if c == ' ' && start == 0 {
            start = i + 1;
        } else if c == ' ' && start < s.len() {
            return &s[start..i];
        }
    }
    if start == 0 {
        return "no second word!";
    }
    &s[start..]
}

fn wc(s: &str) -> u32 {
    let mut count: u32 = 0;
    let mut in_word: bool = false;
    for c in s.chars() {
        if (c == ' ' || c == '\t' || c == '\n') && in_word {
            count += 1;
            in_word = false;
        } else if !((c == ' ' || c == '\t' || c == '\n') || in_word) {
            in_word = true;
        }
    }
    count
}
