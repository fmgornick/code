use std::io;
use std::io::Write;
use termcolor::{Color, ColorChoice, ColorSpec, StandardStream, WriteColor};

extern crate color_name;

enum Message {
    Quit,
    Write(String),
    // Move { x: i32, y: i32 },
    ChangeColor(u8, u8, u8),
}

impl Message {
    fn process(&self) -> bool {
        match self {
            Message::Quit => false,
            Message::Write(s) => {
                println!("{}", s);
                true
            }
            Message::ChangeColor(r, g, b) => {
                let mut stdout = StandardStream::stdout(ColorChoice::Always);
                stdout
                    .set_color(ColorSpec::new().set_fg(Some(Color::Rgb(*r, *g, *b))))
                    .expect("didn't work");
                writeln!(&mut stdout, "RED TEXT").expect("didn't work");
                println!("new color: {}", color_name::Color::similar([*r, *g, *b]));
                true
            }
        }
    }
}

fn main() {
    let mut mes = Message::Write(String::from(""));
    while mes.process() {
        let mut buf = String::new();

        print!("quit, write, or change color? (q/w/c): ");
        io::stdout().flush().unwrap();

        io::stdin().read_line(&mut buf).expect("ERROR");
        let opt: char = buf.chars().nth(0).unwrap();

        match opt {
            'w' => {
                buf = String::new();
                print!("message: ");
                io::stdout().flush().unwrap();
                io::stdin().read_line(&mut buf).expect("ERROR");
                mes = Message::Write(buf);
            }
            'c' => {
                buf = String::new();
                print!("color (r g b separated by spaces): ");
                io::stdout().flush().unwrap();
                io::stdin().read_line(&mut buf).expect("ERROR");
                let nums = buf
                    .trim()
                    .split(' ')
                    .flat_map(str::parse::<u8>)
                    .collect::<Vec<_>>();

                mes = Message::ChangeColor(nums[0], nums[1], nums[2]);
            }
            _ => {
                println!("quiting...");
                mes = Message::Quit;
            }
        }
    }
}
