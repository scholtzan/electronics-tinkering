extern crate sysfs_gpio;

use sysfs_gpio::{Direction, Pin, Edge};
use std::thread::sleep;
use std::time::Duration;

fn main() {
    let speaker_pin = Pin::new(23);

    let control_pins = [21, 22, 17];
    let input_pins: Vec<Pin> = control_pins.iter().map(|&p| Pin::new(p)).collect();

    loop {
        for input in input_pins.iter() {
            input.set_direction(Direction::In);
            input.set_edge(Edge::BothEdges);

            while input.get_value().unwrap() == 1 {
                let frequency = match input.get_pin() {
                    21 => 1,
                    22 => 2,
                    17 => 3,
                    _ => 0
                };

                speaker_pin.set_value(1).unwrap();
                sleep(Duration::from_millis(frequency));
                speaker_pin.set_value(0).unwrap();
                sleep(Duration::from_millis(frequency));
            }
        }
    }
}
