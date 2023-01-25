use std::io;

fn main() {
    let x: i32 = 2;
    //integer i8,i16,i32,i64,i128
    //same with uint

    let floating_point: f32 = 10.931;
    //floating f32,f64
    
    let true_or_false: bool = false;
    //bool: true, false

    let letter: char = 'a';
    //needs to be with ''

    let mut tup: (i32, bool, char) = (1,true,'s');
    tup.0 = 10;
    let mut arr = [1,2,3,4,5,6,7];
    arr[0] = 1;

    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("faild to read line");

    let mut int_input: i64 = input.trim().parse().unwrap();

    let cond = (2 as f32) <= 2.2 && 5 > 2;
    let cond2 = !(false || cond);
    println!("{}",cond2)
}
