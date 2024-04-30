impl Solution {
    pub fn longest_palindrome(s: String) -> i32 {
        /*
            n = s.len()
            O(1) space O(n) time
        */
        let mut counts: [i32; 62] = [0; 62];
        for b in s.bytes() {
            counts[(if b < b'A' {b - b'a'} else {b - b'A'}) as usize] += 1;
        }
        (s.len() as i32) - (match counts.iter().filter(|x| **x & 1 != 0).count() {
            0 | 1 => 0,
            x     => x - 1
        } as i32)
    }
}
