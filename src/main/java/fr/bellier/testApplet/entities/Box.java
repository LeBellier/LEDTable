package fr.bellier.testApplet.entities;

import java.awt.Color;

/**
 *
 * @author bruno
 */
public class Box {

    private final int index;
    private Color color;

    public Box(int index, Color c) {
        this.index = index;
        this.color = c;
    }

    @Override
    public String toString() {
        return "Box{" + "i=" + index + ", color=" + color + '}';
    }

//<editor-fold defaultstate="collapsed" desc=" Get/Set">
    public int getIndex() {
        return index;
    }

    public Color getColor() {
        return color;
    }

    public int getRed() {
        return color.getRed();
    }

    public int getGreen() {
        return color.getGreen();
    }

    public int getBlue() {
        return color.getBlue();
    }

    public void setColor(Color color) {
        this.color = color;
    }
//</editor-fold>
}
