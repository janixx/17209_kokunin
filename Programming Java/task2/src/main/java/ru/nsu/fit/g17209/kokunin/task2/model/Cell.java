package ru.nsu.fit.g17209.kokunin.task2.model;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;

public class Cell {
    private boolean empty;
    private boolean locked;
    private Color content;
    private PropertyChangeSupport support = new PropertyChangeSupport(this);

    public Cell() {
        empty = true;
        locked = true;
        content = Color.WHITE;
    }

    public void addListener(PropertyChangeListener listener) {
        support.addPropertyChangeListener(listener);
        support.firePropertyChange(null,null,null);
    }
    
    public void removeListener(PropertyChangeListener listener) {
        support.removePropertyChangeListener(listener);
    }
    
    public void setLocked(boolean flag) {
        locked = flag;
        support.firePropertyChange(null, null, null);
    }
    
    void setColor(Color color) {
        empty = false;
        locked = true;
        content = color;
        support.firePropertyChange(null, null, null);
    }

    void setWhite() {
        empty = false;
        locked = true;
        content = Color.WHITE;
        support.firePropertyChange(null, null, null);
    }

    void setBlack() {
        empty = false;
        locked = true;
        content = Color.BLACK;
        support.firePropertyChange(null, null, null);
    }

    void clear() {
        empty = true;
        locked = true;
        support.firePropertyChange(null, null, null);
    }

    public boolean isEmpty() { return empty; }
    
    public boolean isLocked() { return locked; }

    public boolean isThisColor(Color color) {
        return ( !empty && (content == color));
    }
    
    public boolean isAnotherColor(Color color) {
        return ( !empty && (content != color) );
    }

    public boolean isWhite() {
        return isThisColor(Color.WHITE);
    }

    public boolean isBlack() {
        return isThisColor(Color.BLACK);
    }
}
