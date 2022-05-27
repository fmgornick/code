use std::io::{self, Write};

fn main() {
    let mut n = String::new();

    print!("number: ");
    io::stdout().flush().unwrap();

    io::stdin().read_line(&mut n).expect("error reading value");
    let n: u32 = match n.trim().parse() {
        Ok(num) => num,
        Err(_) => {
            println!("must be a number");
            return;
        }
    };

    println!("fibonacci: {}", fib(n));
}

fn fib(n: u32) -> u32 {
    match n {
        0 => 1,
        1 => 1,
        _ => fib(n - 1) + fib(n - 2),
    }
}
