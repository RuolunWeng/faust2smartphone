#import "CustomCounter.h"

@implementation CustomCounter {
    float _maxValue;
    float _minValue;
    float _step;
    float _initialValue;
}

- (instancetype)initWithRangeMin:(float)min
                             max:(float)max
                            step:(float)step
                            init:(float)initValue {
    self = [super init];
    if (self) {
        //_currentValue = initValue;
        _maxValue = max;
        _minValue = min;
        _step = step;
        if (initValue >= _minValue && initValue <= _maxValue) {
            _currentValue = initValue;
            _initialValue = initValue;
        } else {
            NSLog(@"Initial value is out of range. Setting to min value.");
            _currentValue = _minValue;
            _initialValue = _minValue;
        }
    }
    return self;
}

- (void)increment {
    _currentValue += _step;
    if (_currentValue > _maxValue) {
        _currentValue = _minValue;
    }
}

- (void)decrement {
    _currentValue -= _step;
    if (_currentValue < _minValue) {
        _currentValue = _maxValue;
    }
}

- (void)reset {
    _currentValue = _initialValue;
}


@end
