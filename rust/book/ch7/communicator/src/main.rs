extern crate communicator;

fn main() {
    communicator::network::connect();
    communicator::network::server::connect();
    communicator::client::connect();
}
