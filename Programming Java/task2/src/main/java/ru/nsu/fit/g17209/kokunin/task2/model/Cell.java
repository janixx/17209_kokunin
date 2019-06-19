package ru.nsu.fit.g17209.kokunin.task2.model;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;

public class Cell {
    private boolean isEmpty;
    private Color content;
    PropertyChangeSupport support = new PropertyChangeSupport(this);

    public Cell() {
        isEmpty = true;
        content = Color.WHITE;
    }

    public void addListener(PropertyChangeListener listener) {
        support.addPropertyChangeListener(listener);
    }
    
    public void removeListener(PropertyChangeListener listener) {
        support.removePropertyChangeListener(listener);
    }
    
    public boolean reverseChip() {
        if (isEmpty) {
            return false;
        }
        content = (content == Color.WHITE ? Color.BLACK : Color.WHITE);
//        support.firePropertyChange("cellChanged", 0, content == Color.WHITE ? 1 : 2);
        support.firePropertyChange(null, null, null);
        return true;
    }
    
    public void setColor(Color color) {
        isEmpty = false;
        content = color;
        support.firePropertyChange(null, null, null);
    }

    public void setWhite() {
        isEmpty = false;
        content = Color.WHITE;
//        support.firePropertyChange(new PropertyChangeEvent(this, null, null, null));
        support.firePropertyChange(null, null, null);
    }

    public void setBlack() {
        isEmpty = false;
        content = Color.BLACK;
//        support.firePropertyChange("cellChanged", 0, 2);
        support.firePropertyChange(null, null, null);
    }

    public void clear() {
        isEmpty = true;
        support.firePropertyChange(null, null, null);
//        support.firePropertyChange("cellChanged", 0, 0);
    }

    public boolean isEmpty() { return isEmpty; }

    public boolean isThisColor(Color color) {
        return (!isEmpty ? (content == color) : false);
    }
    
    public boolean isAnotherColor(Color color) { return (!isEmpty ? (content != color) : false); }

    public boolean isWhite() {
        return isThisColor(Color.WHITE);
    }

    public boolean isBlack() {
        return isThisColor(Color.BLACK);
    }
}
