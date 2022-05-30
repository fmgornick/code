use std::io::{self, stdin, Write};

#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    fn area(&self) -> u32 {
        self.width * self.height
    }

    fn can_hold(&self, other: &Rectangle) -> bool {
        self.width >= other.width && self.height >= other.height
    }

    fn square(length: u32) -> Rectangle {
        Rectangle {
            width: length,
            height: length,
        }
    }
}

fn main() {
    let mut w = String::new();
    let mut h = String::new();

    println!("RECTANGLE THINGY");

    print!("width: ");
    io::stdout().flush().unwrap();
    stdin().read_line(&mut w).expect("couldn't read line");
    let w: u32 = match w.trim().parse() {
        Ok(num) => num,
        Err(_) => {
            println!("NOT A NUMBER");
            return;
        }
    };

    print!("height: ");
    io::stdout().flush().unwrap();
    stdin().read_line(&mut h).expect("couldn't read line");
    let h: u32 = match h.trim().parse() {
        Ok(num) => num,
        Err(_) => {
            println!("NOT A NUMBER");
            return;
        }
    };

    let input = Rectangle {
        width: w,
        height: h,
    };

    let other = Rectangle {
        width: 10,
        height: 10,
    };

    let square = Rectangle::square(w);

    println!("reactangle information: {:?}", input);
    println!("area of rectangle: {}", input.area());
    println!(
        "the inputted rectangle {} hold ours",
        match input.can_hold(&other) {
            true => "can",
            false => "cannot",
        }
    );
    println!("area of square from width: {}", square.area());
}
