pub fn pt_one(input: &str) -> u32 {
    generic(input, 2)
}

pub fn pt_two(input: &str) -> u32 {
    generic(input, 4)
}

pub fn generic(input: &str, window_len: usize) -> u32 {
    input
        .lines()
        .map(|x| x.parse::<u32>().unwrap())
        .collect::<Vec<u32>>()
        .windows(window_len)
        .filter(|arr| arr[window_len - 1] > arr[0])
        .count() as u32
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn pt_one_test() {
        let input = advent::read_file("examples", 1);
        assert_eq!(pt_one(&input), 7)
    }

    #[test]
    fn pt_two_test() {
        let input = advent::read_file("examples", 1);
        assert_eq!(pt_two(&input), 5)
    }
}
