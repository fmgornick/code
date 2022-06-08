use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    let s = &args[1];
    println!(
        "{} {} a palindrome!",
        s,
        match s
            .bytes()
            .take(s.len() / 2)
            .eq(s.bytes().rev().take(s.len() / 2))
        {
            true => String::from("is"),
            false => String::from("is not"),
        }
    );
}
