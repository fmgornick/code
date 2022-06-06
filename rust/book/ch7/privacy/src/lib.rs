mod outermost {
    pub fn middle_function() {}
    fn secret_middle_function() {}

    mod inside {
        pub fn inner_function() {}
        fn secret_inner_function() {}

        fn try_me() {
            crate::outermost::middle_function();
            crate::outermost::secret_middle_function();
            inner_function();
            secret_inner_function();
        }
    }

    fn try_me() {
        middle_function();
        secret_middle_function();
        inside::inner_function();
        inside::secret_inner_function();
    }
}

use outermost::*;

fn try_me() {
    middle_function();
    secret_middle_function();
    inside::inner_function();
    inside::secret_inner_function();
}
