package ru.nsu.fit.g17209.kokunin.task1.core;

public class MutableInt extends Number implements Comparable<MutableInt> {
    private int value;

    public MutableInt(int i){
        value = i;
    }

    @Override
    public int intValue() {
        return value;
    }

    @Override
    public long longValue() {
        return (long)value;
    }

    @Override
    public float floatValue() {
        return (float)value;
    }

    @Override
    public double doubleValue() {
        return (double)value;
    }

    @Override
    public String toString() {
        return Integer.toString(value);
    }

    public void increment() {
        value++;
    }

    public void decrement() {
        value--;
    }

    @Override
    public int compareTo(MutableInt another) {
        return (this.value  < another.intValue() ? -1 : (this.value == another.intValue() ? 0 : 1));
    }
}