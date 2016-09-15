/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package fr.bellier.testApplet;

import java.awt.Color;
import java.util.LinkedList;
import java.util.List;

/**
 *
 * @author bruno
 */
public class RandomGame extends TableGame {

    private final List<Integer> availableSquares = new LinkedList<Integer>();

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(RandomGame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(RandomGame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(RandomGame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(RandomGame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                RandomGame.getSingleton();
            }
        });
    }

    public static TableGame getSingleton() {
        if (game == null) {
            game = new RandomGame();
        }
        return game;
    }

    RandomGame() {
        super();
        setAllSquare(Color.BLACK);
        for (int i = 0; i < getSize(); i++) {
            availableSquares.add(i);
        }
    }

    /**
     *
     * @return index of the chosen square
     */
    public int nextStep() {

        NextStepThread nextStepThread = new NextStepThread();
        nextStepThread.start();
        return 1;
    }

    void restart() {
        setAllSquare(Color.BLACK);
        availableSquares.clear();
        for (int i = 0; i < getSize(); i++) {
            availableSquares.add(i);
        }
    }

    class NextStepThread extends Thread {

        @Override
        public void run() {
            int higher = availableSquares.size();
            int idWinnerSquare = (int) (Math.random() * higher);
            int nbIntermediateSquare = (int) (Math.random() * 10);
            for (int i = 0; i < nbIntermediateSquare + 10; i++) {
                int idCurrentSquare = (int) (Math.random() * higher);
                setSquare(availableSquares.get(idCurrentSquare), Color.green, Boolean.TRUE);

                try {
                    Thread.sleep(50);
                } catch (InterruptedException ex) {
                    Thread.currentThread().interrupt();
                }
                setSquare(availableSquares.get(idCurrentSquare), Color.black, Boolean.TRUE);
            }
            setSquare(availableSquares.get(idWinnerSquare), Color.red, Boolean.TRUE);
            availableSquares.remove(idWinnerSquare);
        }

    }
}
