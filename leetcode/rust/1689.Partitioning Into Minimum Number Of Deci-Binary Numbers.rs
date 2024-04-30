impl Solution {
  pub fn min_partitions(n: String) -> i32 {
    /*
        n = n.len()
        O(1) space O(n) time
    */
    n.bytes().map(|x| x - b'0').max().unwrap() as i32
  }
}
