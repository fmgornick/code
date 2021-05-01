extern crate rand;
use std::io;
use std::cmp::Ordering;
use rand::Rng;

fn main() {
    println!("welcome to the guessing game!!");

    let secret_number = rand::thread_rng().gen_range(1,101);
    println!("the secret number is {}", secret_number);

    println!("please input your guess");
    loop {
        let mut guess = String::new();
        io::stdin().read_line(&mut guess).expect("failed to read line");

        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => {
                println!("please enter a number");
                continue;
            }
        };

        match guess.cmp(&secret_number) {
            Ordering::Less => println!("too low"),
            Ordering::Greater => println!("too high"),
            Ordering::Equal => {
                println!("you got it!");
                break;
            }
        }
    }
}
