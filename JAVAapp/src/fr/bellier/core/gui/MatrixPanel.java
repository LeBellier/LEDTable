package fr.bellier.core.gui;

import java.awt.Color;
import java.awt.Dimension;
import java.util.LinkedList;
import java.util.List;
import javax.swing.JLabel;

/**
 *
 * @author LeBellier
 */
public class MatrixPanel extends javax.swing.JPanel {

    /**
     * Creates new form matrixPanel
     *
     * @param maxRow
     * @param maxCol
     */
    public MatrixPanel(int maxRow, int maxCol) {
        initComponents();
        initSpecificComponents(maxRow, maxCol);
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        setLayout(new java.awt.GridLayout(1, 0));
    }// </editor-fold>//GEN-END:initComponents

    // Variables declaration - do not modify//GEN-BEGIN:variables
    // End of variables declaration//GEN-END:variables
    private final List<JLabel> cellLbls = new LinkedList<JLabel>();

    private void initSpecificComponents(int maxRow, int maxCol) {
        setLayout(new java.awt.GridLayout(maxRow, maxCol));
        Dimension dmnsn = new Dimension(40 * maxCol, 40 * maxRow);
        setMinimumSize(dmnsn);
        setMaximumSize(dmnsn);
        setPreferredSize(dmnsn);
        for (int row = 0; row < maxRow; row++) {
            for (int column = 0; column < maxCol; column++) {
                JLabel currentWorkingLabel = new javax.swing.JLabel();
                currentWorkingLabel.setOpaque(true);
                cellLbls.add(currentWorkingLabel);
                add(currentWorkingLabel);
            }
        }
    }

    public void setColor(int index, Color color) {
        cellLbls.get(index).setBackground(color);
    }
}
