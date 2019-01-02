extern crate sysfs_gpio;

use sysfs_gpio::{Direction, Pin};
use std::thread::sleep;
use std::time::Duration;

fn main() {
    let pin_numbers = [7, 8, 25, 24];
    let pins: Vec<Pin> = pin_numbers.iter().map(|&p| Pin::new(p)).collect();

    let steps =
        [[1,0,0,1],
        [1,0,0,0],
        [1,1,0,0],
        [0,1,0,0],
        [0,1,1,0],
        [0,0,1,0],
        [0,0,1,1],
        [0,0,0,1]];

    let mut step_counter = 0;

    loop {
        for i in 0..4 {
            pins[i].set_value(steps[step_counter][i]).unwrap();
        }

        step_counter += 1;

        if step_counter >= steps.len() {
            step_counter = 0;
        }

        sleep(Duration::from_millis(1));
    }
}
